/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 02:04:38 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 02:04:51 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_invalid_op(t_token *token_l)
{
	t_token	*cur;

	if (!token_l)
		return (1);
	cur = token_l;
	while (cur)
	{
		if (cur->next)
		{
			if (is_logical_op(cur->type))
			{
				if (is_logical_op(cur->next->type))
					return (1);
			}
			else if (is_redir(cur->type))
			{
				if (is_redir(cur->next->type) || is_logical_op(cur->next->type))
					return (1);
			}
		}
		cur = cur->next;
	}
	return (0);
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
			if (!is_word(cur->next->type))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}

int	validate_subshell(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (check_last_node(tokens)
		|| check_first_node(tokens)
		|| check_invalid_op(tokens)
		|| check_unbalanced_parentheses(tokens)
		|| check_empty_parentheses(tokens)
		|| check_invalid_redir(tokens))
		return (1);
	return (0);
}

int	validate_syntax(t_data *data)
{
	if (!data->token_list)
		return (0);
	if (data->has_error)
		return (1);
	if (check_first_node(data->token_list))
		return (syntax_error("unexpected token", data));
	else if (check_last_node(data->token_list))
		return (syntax_error("unexpected token", data));
	else if (check_invalid_op(data->token_list))
		return (syntax_error("unexpected token", data));
	else if (check_unbalanced_parentheses(data->token_list))
		return (syntax_error("unexpected token", data));
	else if (check_empty_parentheses(data->token_list))
		return (syntax_error("empty parentheses", data));
	else if (check_invalid_redir(data->token_list))
		return (syntax_error("unexpected redirection", data));
	else if (check_invalid_subshell_content(data))
		return (syntax_error("unexpected token", data));
	return (0);
}
