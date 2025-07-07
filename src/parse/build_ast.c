/*build_ast.c*/

#include "../../include/minishell.h"

t_ast	*create_node_ast(char *value, t_type type, t_gc *gc)
{
	t_ast	*node;

	node = gc_malloc(gc, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	// node->value = value; (ANTES)
	if (value != NULL)
		node->value = gc_strdup(value, gc); // Garante uma cópia propria gerenciada pelo coletor (CAIO) 
	else
		node->value = NULL;
	node->is_builtin = false;
	node->args = NULL;
	node->redir = NULL; // Somente essa linha já resolve o segfault (CAIO)
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int get_args_len(t_token *tokens)
{
	int		count;
	t_token	*cur;

    count = 0;
    cur = tokens;
    while (cur && (is_word(cur->type) || cur->type == ASSIGNMENT))
    {
        count++;
        cur = cur->next;
    }
    return (count);
}

char	**extract_args(t_token *tokens, t_gc *gc)
	{
	int		count;
	char	**args;
	t_token	*cur;

    if (!tokens)
        return (NULL);
    count = get_args_len(tokens);
    args = gc_malloc(gc, sizeof(char *) * (count + 1));
    if (!args)
        return (NULL);
    cur = tokens;
    count = 0;
    while (cur && (is_word(cur->type) || cur->type == ASSIGNMENT))
    {
		// args[count++] = cur->value; (ANTES)
        args[count++] = gc_strdup(cur->value, gc); // Usa gc_strdup para alocar e copiar cur->value no coletor de lixo, garantindo que args armazene uma cópia segura da string (CAIO)
        cur = cur->next;
    }
    args[count] = NULL;
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
	{
		fprintf(stderr, "Error: parsing failed, AST is NULL\n");
		return ;
	}
}
