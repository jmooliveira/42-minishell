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

static t_token	*skip_redirs(t_token *tokens)
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

static void	handle_redirs(t_ast *node, t_token *cur, t_gc *gc)
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
