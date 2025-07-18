/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:59:26 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 01:59:27 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_clean_args_len(t_token *tokens)
{
	int		count;
	bool	non_empty_seen;
	t_token	*cur;

	non_empty_seen = false;
	count = 0;
	cur = tokens;
	while (cur && (is_word(cur->type) || cur->type == ASSIGNMENT))
	{
		if (cur->value && (non_empty_seen || cur->value[0] != '\0'))
		{
			non_empty_seen = true;
			count++;
		}
		cur = cur->next;
	}
	return (count);
}

static int	count_args(t_token *cur)
{
	int	count;

	count = 0;
	while (cur)
	{
		if (is_word(cur->type) || cur->type == ASSIGNMENT)
			count++;
		else if (is_redir(cur->type) && cur->next)
			cur = cur->next;
		cur = cur->next;
	}
	return (count);
}

char	**extract_args(t_token *tokens, t_gc *gc)
{
	t_token	*cur;
	int		arg_count;
	char	**args;
	int		i;

	arg_count = count_args(tokens);
	args = gc_malloc(gc, sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	cur = tokens;
	i = 0;
	while (cur)
	{
		if (is_word(cur->type) || cur->type == ASSIGNMENT)
			args[i++] = gc_strdup(cur->value, gc);
		else if (is_redir(cur->type) && cur->next)
			cur = cur->next;
		cur = cur->next;
	}
	args[i] = NULL;
	return (args);
}

t_ast	*build_ast(t_token *tokens, t_gc *gc)
{
	t_token	*op;

	if (!tokens || !gc)
		return (NULL);
	if (is_subshell(tokens))
		return (parse_subshell(tokens, gc));
	op = find_and_or(tokens);
	if (op)
		return (parse_operator(tokens, op, gc));
	op = find_pipe(tokens);
	if (op)
		return (parse_operator(tokens, op, gc));
	return (parse_cmd(tokens, gc));
}

void	parse(t_data *data)
{
	data->tree = build_ast(data->token_list, data->gc);
	if (!data->tree)
		return ;
}
