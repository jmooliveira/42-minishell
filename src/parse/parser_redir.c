/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 02:00:04 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 02:00:05 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	init_heredoc(t_redir *redir, char *filename, t_gc *gc)
{
	redir->delim = gc_strdup(filename, gc);
	redir->filename = generate_heredoc_tmp(gc);
	if (exec_heredoc(redir->filename, redir->delim) != 0)
	{
		g_signal = SIGINT;
		return (1);
	}
	return (0);
}

void	add_redir(t_ast *node, t_type type, char *filename, t_gc *gc)
{
	t_redir	*new;
	t_redir	*cur;

	new = gc_malloc(gc, sizeof(t_redir));
	if (!new)
		return ;
	new->type = type;
	new->filename = trim_quotes(filename, gc);
	new->delim = NULL;
	new->next = NULL;
	if (type == HEREDOC && init_heredoc(new, filename, gc))
		return ;
	if (!node->redir)
		node->redir = new;
	else
	{
		cur = node->redir;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

t_token	*skip_redirs(t_token *tokens)
{
	t_token	*cur;

	cur = tokens;
	while (cur && is_redir(cur->type))
	{
		if (!cur->next)
			break ;
		cur = cur->next->next;
	}
	return (cur);
}

void	handle_redirs(t_ast *node, t_token *cur, t_gc *gc)
{
	while (cur)
	{
		if (is_redir(cur->type) && cur->next)
		{
			add_redir(node, cur->type, cur->next->value, gc);
			cur = cur->next;
		}
		cur = cur->next;
	}
}
