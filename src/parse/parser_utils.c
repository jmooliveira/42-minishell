/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 02:00:21 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 02:00:22 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_operator(t_type type)
{
	return (type == OR || type == AND || type == PIPE);
}

bool	is_redir_bool(t_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC);
}

t_token	*create_token_copy(t_token *src, t_gc *gc)
{
	t_token	*new;

	new = gc_malloc(gc, sizeof(t_token));
	if (!new)
		return (NULL);
	*new = *src;
	new->type = src->type;
	new->expandable = src->expandable;
	new->next = NULL;
	if (src->value)
		new->value = gc_strdup(src->value, gc);
	else
		new->value = NULL;
	return (new);
}

t_token	*slice_tokens(t_token *start, t_token *end, t_gc *gc)
{
	t_token	*head;
	t_token	*tail;
	t_token	*cur;
	t_token	*new_token;

	head = NULL;
	tail = NULL;
	cur = start;
	while (cur)
	{
		new_token = create_token_copy(cur, gc);
		if (!new_token)
			return (NULL);
		if (!head)
			head = new_token;
		else
			tail->next = new_token;
		tail = new_token;
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (head);
}

t_ast	*create_node_ast(char *value, t_type type, t_gc *gc)
{
	t_ast	*node;

	node = gc_malloc(gc, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	if (value != NULL)
		node->value = gc_strdup(value, gc);
	else
		node->value = NULL;
	node->is_builtin = false;
	node->args = NULL;
	node->redir = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
