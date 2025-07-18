/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 02:04:45 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 02:04:46 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_token	*get_token_before(t_token *list, t_token *target)
{
	t_token	*cur;

	cur = list;
	while (cur && cur->next != target)
		cur = cur->next;
	return (cur);
}

t_token	*find_subshell_end(t_token *start)
{
	t_token	*cur;
	int		balance;

	cur = start;
	balance = 1;
	while (cur)
	{
		if (cur->type == PAR_OPEN)
			balance++;
		else if (cur->type == PAR_CLOSE)
			balance--;
		if (balance == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
