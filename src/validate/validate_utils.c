/*validate_utils.c*/

#include "../../include/minishell.h"

int	is_logical_op(t_type type)
{
	return (type == PIPE || type == OR || type == AND);
}

int	is_redir(t_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC);
}

int	is_word(t_type type)
{
	return (type == WORD_D || type == WORD_S || type == WORD);
}

int	check_invalid_redir(t_token *token_l)
{
	t_token	*cur;

	cur = token_l;
	while (cur)
	{
		if (is_redir(cur->type))
		{
			if (!cur->next)
				return (1);
			if (!is_word(cur->next->type) && cur->next->type != PAR_OPEN)
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}

int	check_empty_parentheses(t_token *token_l)
{
	t_token	*cur;

	cur = token_l;
	while (cur && cur->next)
	{
		if (cur->type == PAR_OPEN && cur->next->type == PAR_CLOSE)
			return (1);
		cur = cur->next;
	}
	return (0);
}
