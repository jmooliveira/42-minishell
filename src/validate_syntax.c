/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:32:33 by ancarol9          #+#    #+#             */
/*   Updated: 2025/05/29 19:33:01 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	syntax_error(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	return (1);
}


int	check_pipe(t_token *list)
{
	if (list && list->type == PIPE)
		return(syntax_error("Error: pipe at begning"));
	while (list)
	{
		if (list->type == PIPE && (!list->next || list->next->type == PIPE))
			return(syntax_error("Error: invalid pipe"));
		list = list->next;
	}
	return (0);
}

// int	check_operator_sequence(t_token *list)
// {
// 	if (list && (list->type == AND || list->type == OR || list->type == REDIRECT_IN || list->type == REDIRECT_OUT || list->type == HEREDOC || list->type == APPEND))
// 		return (syntax_error("Error: invalid operator"));
// 	while (list)
// 	{
// 		if (list->type == AND || list->type == OR || list->type == REDIRECT_IN || list->type == REDIRECT_OUT || list->type == HEREDOC || list->type == APPEND)
// 		{
// 			if (!list->next || list->next->type)
// 		}
// 		list = list->next;
// 	}
// }


// int	validate_syntax(t_token *token_list)
// {
// 	// pipe no inicio e no fim
// 	if (check_pipe(token_list))
// 		return (1);
// 	// operadores duplicados ?
// 	// parenteses desbalanceados
// 	// parenteses mal posicionado
// 	// aspas nao fechadas
// 	// nada entre operadores
// 	// redirecionamento incompleto ?
// }
