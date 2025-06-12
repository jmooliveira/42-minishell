/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeff <jeff@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:43:22 by ancarol9          #+#    #+#             */
/*   Updated: 2025/06/12 19:31:29 by jeff             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*utils_debug.c*/

#include "../../include/minishell.h"

void	print_token(t_token *token_list)
{
	int i = 0;
	t_token	*current = token_list;

	while (current)
	{
		printf("token%d:, id: %d, value: %s\n", i, current->type, current->value);
		current = current->next;
		i++;
	}
}