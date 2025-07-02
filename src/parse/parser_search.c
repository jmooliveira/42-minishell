#include "../../include/minishell.h"

t_token   *find_operator(t_token *tokens)
{
	t_token     *cur;
	t_token     *last;
	int         par_count;

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
