/*parser.c*/

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
	t_ast	*node;

	if (!tokens)
		return (NULL);
	node = create_node_ast(tokens->value, tokens->type, gc);
	if (!node)
		return (NULL);
	node->args = extract_args(tokens, gc);
	return (node);
}

void	handle_start_redir(t_token *op, t_ast *node, t_gc *gc)
{
	t_token	*target;
	t_token	*cmd;

	if (!op->next || !op->next->next)
		return ;
	target = slice_tokens(op->next, op->next, gc);
	cmd = slice_tokens(op->next->next, NULL, gc);
	node->left = build_ast(cmd, gc);
	node->right = build_ast(target, gc);
}

t_ast	*parse_redir(t_token *tokens, t_token *op, t_gc *gc)
{
	t_ast	*node;
	t_token	*cur;
	t_token	*left;
	t_token	*right;

	node = create_node_ast(op->value, op->type, gc);
	if (!node)
		return (NULL);
	if (tokens == op)
	{
		handle_start_redir(op, node, gc);
		return (node);
	}
	cur = tokens;
	while (cur && cur->next != op)
		cur = cur->next;
	left = slice_tokens(tokens, cur, gc);
	node->left = build_ast(left, gc);
	if (!op->next)
		return (NULL);
	right = slice_tokens(op->next, op->next, gc);
	node->right = build_ast(right, gc);
	return (node);
}
