/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:32:33 by ancarol9          #+#    #+#             */
/*   Updated: 2025/05/30 17:46:12 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	syntax_error(char *msg, t_data *data)
{
	ft_putstr_fd("Error: syntaxe error near ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	data->exit_status = 2;
	return (1);
}

int is_logical_op(t_type type)
{
	return (type == PIPE || type == OR || type == AND);
}

int is_redir(t_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == APPEND || type == HEREDOC);
}

int		check_first_node(t_token *token_l)
{
	if (!token_l)
		return (1);
	if (is_logical_op(token_l->type) || token_l->type == PAR_CLOSE)
		return (1);
	return (0);
}

int		check_last_node(t_token *token_l)
{
	t_token	*last;

	if (!token_l)
		return (1);
	last = ft_token_last(token_l);
	if (is_logical_op(last->type) || is_redir(last->type) || last->type == PAR_OPEN)
		return (1);
	return (0);
}

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
				if (is_logical_op(cur->next->type) || is_redir(cur->next->type))
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

int	check_unbalanced_parentheses(t_token *token_list)
{
	t_token	*cur;

	cur = token_list;
	while (cur)
	{
		if (cur->type == PAR_OPEN)
		{
			cur = cur->next;
			while (cur)
			{
				if (cur->type == PAR_CLOSE)
					return (0);
				cur = cur->next;
			}
			
		}
		cur = cur->next;
	}
	return (1);
}


int	validate_syntax(t_data *data)
{
	// operador no inicio
	if (check_first_node(data->token_list))
		return (syntax_error("unexpected token", data));
	// operador no final
	else if (check_last_node(data->token_list))
		return (syntax_error("unexpected token", data));
	// operadores duplicados
	else if (check_invalid_op(data->token_list))
		return (syntax_error("unexpected token", data));
	// parenteses desbalanceados
	else if (check_unbalanced_parentheses(data->token_list))
		return (syntax_error("unexpected token", data));
	// parenteses mal posicionado
	// aspas nao fechadas
	// redirecionamento incompleto ?
}
