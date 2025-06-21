#include "../../include/minishell.h"

bool    is_operator(t_type type)
{
	return (type == OR || type == AND || type == PIPE);
}

bool    is_redir_bool(t_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == APPEND || type == HEREDOC);
}

void	handle_error(char *msg, t_data *data)
{
	ft_putstr_fd("Error:", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	data->exit_status = 2;
	gc_clear(data->gc);
	exit(EXIT_FAILURE);
}


int is_subshell(t_token *tokens)
{
    t_token *cur;
	t_token *last;
	int     par_count;
    
	if (!tokens || tokens->type != PAR_OPEN)
        return (0);
	last = tokens;
	while (last->next)
        last = last->next;
	if (last->type != PAR_CLOSE)
        return (0);
	cur = tokens;
	par_count = 0;
	while (cur)
	{
        if (cur->type == PAR_OPEN)
            par_count++;
		else if (cur->type == PAR_CLOSE)
            par_count--;
		if (par_count == 0 && cur != last)
            return (0);
		cur = cur->next;
	}
	return (1);
}

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

t_token   *find_operator(t_token *tokens)
{
	t_token     *cur;
	t_token     *last;
	int         par_count;

	if (!tokens)
		return (NULL);
	cur = tokens;
	par_count = 0;
	while (cur)
	{
		if (cur->type == PAR_OPEN)
			par_count++;
		else if (cur->type == PAR_CLOSE)
			par_count--;
		else if (par_count == 0 && is_operator(cur->type))
			last = cur;
		cur = cur->next;
	}
	return (last);
}
t_token	*find_redir(t_token *tokens)
{
	t_token	*cur;
	t_token	*last;
	int		par_count;

	if (!tokens)
		return (NULL);
	cur = tokens;
	par_count = 0;
	last = NULL;
	while (cur)
	{
		if (cur->type == PAR_OPEN)
			par_count++;
		else if (cur->type == PAR_CLOSE)
			par_count--;
		if (is_redir_bool(cur->type) && par_count == 0)
			last = cur;
		cur = cur->next;
	}
	return (last);
}

t_token *split_tokens(t_token *tokens, t_token *op)
{
    t_token *cur;
    t_token *right;

    cur = NULL;
    if (!tokens || !op)
        return (NULL);
    right = op->next;
    if (tokens == op)
    {
        op->next = NULL;
        return (right);
    }
    cur = tokens;
    while (cur && cur->next != op)
        cur = cur->next;
    if (cur)
        cur->next = NULL;
    op->next = NULL;
    return (right);
}

t_token *create_token_copy(t_token *src, t_gc *gc)
{
    t_token *new;

    new = gc_malloc(gc, sizeof(t_token));
    if (!new)
        return (NULL);
    *new = *src;
    new->next = NULL;
    if (src->value)
        new->value = gc_strdup(src->value, gc);
    return (new);
}

t_token *slice_tokens(t_token *start, t_token *end, t_gc *gc)
{
    t_token *head = NULL;
    t_token *tail = NULL;
    t_token *cur = start;

    while (cur)
    {
        t_token *new_token = create_token_copy(cur, gc);
        if (!new_token)
            return (NULL);
        if (!head)
            head = tail = new_token;
        else
        {
            tail->next = new_token;
            tail = new_token;
        }
        if (cur == end) // quebra aqui se end for alcançado
            break;
        cur = cur->next;
    }
    return head;
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

t_ast	*parse_subshell(t_token *tokens, t_gc *gc)
{
	t_ast	*node;
    t_token *last;
    t_token *penult;
    t_token *inner_tokens;

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

t_ast   *parse_operator(t_token *tokens, t_token *op, t_gc *gc)
{
    t_ast   *node;
    t_token *right;
    t_token *left;
    t_token *cur;

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

t_ast   *parse_cmd(t_token *tokens, t_gc *gc)
{
    t_ast   *node;

    if (!tokens)
        return (NULL);
    node = create_node_ast(tokens->value, tokens->type, gc);
    if (!node)
        return (NULL);
    node->args = extract_args(tokens, gc);
    return (node);
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
	// op = find_redir_bool(tokens);
	// if (op)
	// 	return (parse_redir(tokens, op, gc));
	return (parse_cmd(tokens, gc));

}


static void	print_indent(int depth)
{
	for (int i = 0; i < depth; i++)
		printf("  ");
}

static const char *get_type_name(t_type type)
{
	if (type == WORD || type == WORD_S || type == WORD_D) return "WORD";
	if (type == REDIR_IN) return "REDIR_IN";
	if (type == REDIR_OUT) return "REDIR_OUT";
	if (type == APPEND) return "APPEND";
	if (type == HEREDOC) return "HEREDOC";
	if (type == AND) return "AND";
	if (type == OR) return "OR";
	if (type == PIPE) return "PIPE";
	if (type == PAR_OPEN) return "PAR_OPEN";
	if (type == PAR_CLOSE) return "PAR_CLOSE";
	if (type == SUBSHELL) return "SUBSHELL";
	if (type == ASSIGNMENT) return "ASSIGNMENT";
	if (type == NONE) return "NONE";
	return "UNKNOWN";
}

void	print_ast(t_ast *node, int depth)
{
	if (!node)
		return ;

	print_indent(depth);
	printf("• [%s] \"%s\"\n", get_type_name(node->type),
		node->value ? node->value : "NULL");

	if (node->args)
	{
		print_indent(depth + 1);
		printf("args: ");
		for (int i = 0; node->args[i]; i++)
			printf("\"%s\" ", node->args[i]);
		printf("\n");
	}

	if (node->left)
	{
		print_indent(depth);
		printf("├─ left:\n");
		print_ast(node->left, depth + 1);
	}
	if (node->right)
	{
		print_indent(depth);
		printf("└─ right:\n");
		print_ast(node->right, depth + 1);
	}
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


// AQUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII!

// minishell$ echo $HOME
// token0:, id: 0, value: echo
// token1:, id: 0, value: /nfs/homes/ancarol9
// minishell$ echo "$HOME"
// token0:, id: 0, value: echo
// token1:, id: 2, value: /nfs/homes/ancarol9
// minishell$ echo '$HOME'
// token0:, id: 0, value: echo
// token1:, id: 1, value: $HOME
// minishell$ echo "'$HOME'"
// token0:, id: 0, value: echo
// token1:, id: 2, value: '/nfs/homes/ancarol9'
// minishell$ echo $HOME-'$USER'
// token0:, id: 0, value: echo
// token1:, id: 0, value: /nfs/homes/ancarol9-'ancarol9'
// minishell$ 

// o Marcos deu a dica de tirar as aspas na hora da expansao nao no momento de tokenizar.