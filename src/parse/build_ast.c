#include "../../include/minishell.h"

t_ast   *create_node_ast(char *value, t_type type, t_gc *gc)
{
    t_ast   *node;

    node = gc_malloc(gc, sizeof(t_ast));
    if (!node)
        return (NULL);
    node->type = type;
    node->value = value;
    node->args = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

int get_args_len(t_token *tokens)
{
    int     count;
    t_token *cur;

    count = 0;
    cur = tokens;
    while (cur && (cur->type == WORD || cur->type == ASSIGNMENT))
    {
        count++;
        cur = cur->next;
    }
    return (count);
}

char    **extract_args(t_token *tokens, t_gc *gc)
{
    int     count;
    char    **args;
    t_token *cur;

    if (!tokens)
        return (NULL);
    count = get_args_len(tokens);
    args = gc_malloc(gc, sizeof(char *) * (count + 1));
    if (!args)
        return (NULL);
    cur = tokens;
    count = 0;
    while (cur && (cur->type == WORD || cur->type == ASSIGNMENT))
    {
        args[count++] = cur->value;
        cur = cur->next;
    }
    args[count] = NULL;
    return (args);
}

t_ast   *build_ast(t_token *tokens, t_gc *gc)
{
	t_token    *op;

	if (!tokens || !gc)
		return (NULL);
	if (is_subshell(tokens))
		return (parse_subshell(tokens, gc));
	op = find_operator(tokens);
	if (op)
		return (parse_operator(tokens, op, gc));
	op = find_redir(tokens);
	if (op)
		return (parse_redir(tokens, op, gc));
	return (parse_cmd(tokens, gc));

}

void	parse(t_data *data)
{
	data->tree = build_ast(data->token_list, data->gc);
	if (!data->tree)
	{
		fprintf(stderr, "Error: parsing failed, AST is NULL\n");
		return;
	}
	print_ast(data->tree, 0);
}
