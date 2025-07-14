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

char	*generate_heredoc_tmp(t_gc *gc)
{
	static int	id = 0;
	char		*tmp;
	char		*id_str;
	char		*pid_str;
	char		*suffix;

	id_str = gc_itoa(id++, gc);
	pid_str = gc_itoa(getpid(), gc);
	suffix = gc_strjoin(pid_str, "_", gc);
	suffix = gc_strjoin(suffix, id_str, gc);
	tmp = gc_strjoin("/tmp/.hd_tmp_", suffix, gc);
	return (tmp);
}

void	add_redir(t_ast *node, t_type type, char *filename, t_gc *gc)
{
	t_redir	*new;
	t_redir	*cur;
	// t_token *next_token;
	// char *new_filename;

	new = gc_malloc(gc, sizeof(t_redir));
	if (!new)
		return ;
	new->type = type;
	new->filename = gc_strdup(filename, gc); // Duplica a string `filename` usando o alocador do GC, garantindo que `new->filename` seja gerenciado automaticamente (CAIO)
	// next_token = node->tokens;
	// while (next_token && is_word(next_token->type))
	// {
	// 	new_filename = gc_strjoin(new->filename, next_token->value, gc);
	// 	gc_free(gc, new->filename);
	// 	new->filename = new_filename;
	// 	next_token = next_token->next;
	// }
	new->delim = NULL;
	new->next = NULL;
	new->hd_written = false;
	if (type == HEREDOC)
	{
		new->filename = generate_heredoc_tmp(gc);
		new->delim = filename;
	}
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

t_ast	*parse_cmd(t_token *tokens, t_gc *gc)
{
	t_ast	*node;
	t_token	*cur;
	t_token	*cmd_token;

	cur = tokens;
	cmd_token = NULL;
	if (!tokens)
		return (NULL);
	while (cur && is_redir(cur->type))
	{
		if (cur->next)
			cur = cur->next->next; // Pula o redirecionamento e seu argumento
		else
			break ;
	}
	if (!cmd_token)// Se não houver comando após os redirecionamentos, use o primeiro token
		cmd_token = cur;
	else
		cmd_token = tokens;
	node = create_node_ast(tokens->value, tokens->type, gc);
	if (!node)
		return (NULL);
	if (is_builtin(tokens->value))
		node->is_builtin = true;
	node->args = extract_args(tokens, gc);
	cur = tokens;
	while (cur)
	{
		if (is_redir(cur->type) && cur->next)
		{
			add_redir(node, cur->type, cur->next->value, gc);
			cur = cur->next;
		}
		cur = cur->next;
	}
	return (node);
}
