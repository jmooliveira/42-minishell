/*build_ast.c*/

#include "../../include/minishell.h"

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
