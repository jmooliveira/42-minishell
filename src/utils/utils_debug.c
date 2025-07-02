/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:43:22 by ancarol9          #+#    #+#             */
/*   Updated: 2025/06/21 18:47:30 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*utils_debug.c*/

#include "../../include/minishell.h"

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

void print_token(t_token *token_list)
{
	int i = 0;
	t_token *current = token_list;

	while (current)
	{
		printf("token%d:, type: %s, value: %s\n",
			i, get_type_name(current->type), current->value);
		current = current->next;
		i++;
	}
}
