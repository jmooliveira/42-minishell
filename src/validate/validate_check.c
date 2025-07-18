/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 02:04:35 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 02:04:35 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_first_node(t_token *token_l)
{
	if (!token_l)
		return (1);
	if (is_logical_op(token_l->type) || token_l->type == PAR_CLOSE)
		return (1);
	return (0);
}

int	check_last_node(t_token *token_l)
{
	t_token	*last;

	if (!token_l)
		return (1);
	last = ft_token_last(token_l);
	if (is_logical_op(last->type) || is_redir(last->type)
		|| last->type == PAR_OPEN)
		return (1);
	return (0);
}

int	check_unbalanced_parentheses(t_token *token_list)
{
	int		balance;
	t_token	*cur;

	cur = token_list;
	balance = 0;
	while (cur)
	{
		if (cur->type == PAR_OPEN)
			balance++;
		else if (cur->type == PAR_CLOSE)
			balance--;
		if (balance < 0)
			return (1);
		cur = cur->next;
	}
	return (balance != 0);
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

int	check_invalid_subshell_content(t_data *data)
{
	t_token	*cur;
	t_token	*end;
	t_token	*sub;
	t_token	*start;
	int		ret;

	cur = data->token_list;
	while (cur)
	{
		if (cur->type == PAR_OPEN)
		{
			start = cur->next;
			end = find_subshell_end(start);
			if (!end)
				return (1);
			end = get_token_before(data->token_list, end);
			sub = slice_tokens(start, end, data->gc);
			ret = validate_subshell(sub);
			if (ret)
				return (1);
			cur = end;
		}
		cur = cur->next;
	}
	return (0);
}
