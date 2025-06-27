/*parser_utils.c*/

#include "../../include/minishell.h"

bool    is_operator(t_type type)
{
	return (type == OR || type == AND || type == PIPE);
}

bool    is_redir_bool(t_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == APPEND || type == HEREDOC);
}

t_token *create_token_copy(t_token *src, t_gc *gc)
{
    t_token *new;

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

void	handle_error(char *msg, t_data *data)
{
	ft_putstr_fd("Error:", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	data->exit_status = 2;
	gc_clear(data->gc);
	exit(EXIT_FAILURE);
}