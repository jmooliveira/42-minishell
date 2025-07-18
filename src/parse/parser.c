/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 02:00:26 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 02:01:04 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*parse_subshell(t_token *tokens, t_gc *gc)
{
	t_ast	*node;
	t_token	*last;
	t_token	*penult;
	t_token	*inner_tokens;

	node = create_node_ast(NULL, SUBSHELL, gc);
	if (!node)
		return (NULL);
	last = tokens;
	while (last->next)
		last = last->next;
	penult = tokens;
	while (penult && penult->next != last)
		penult = penult->next;
	inner_tokens = slice_tokens(tokens->next, penult, gc);
	node->left = build_ast(inner_tokens, gc);
	return (node);
}

t_ast	*parse_operator(t_token *tokens, t_token *op, t_gc *gc)
{
	t_ast	*node;
	t_token	*right;
	t_token	*left;
	t_token	*cur;

	node = create_node_ast(NULL, op->type, gc);
	if (!node)
		return (NULL);
	cur = tokens;
	while (cur && cur->next != op)
		cur = cur->next;
	if (cur)
		left = slice_tokens(tokens, cur, gc);
	else
		left = NULL;
	right = slice_tokens(op->next, NULL, gc);
	node->left = build_ast(left, gc);
	node->right = build_ast(right, gc);
	return (node);
}

t_ast	*parse_cmd(t_token *tokens, t_gc *gc)
{
	t_ast		*node;
	t_token		*cmd_token;
	t_token		*cur;

	if (!tokens)
		return (NULL);
	cur = skip_redirs(tokens);
	if (cur)
		cmd_token = cur;
	else
		cmd_token = tokens;
	node = create_node_ast(tokens->value, tokens->type, gc);
	if (!node)
		return (NULL);
	if (is_builtin(tokens->value))
		node->is_builtin = true;
	node->args = extract_args(tokens, gc);
	handle_redirs(node, tokens, gc);
	return (node);
}
