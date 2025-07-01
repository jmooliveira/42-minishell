/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeff <jeff@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:43:22 by ancarol9          #+#    #+#             */
/*   Updated: 2025/06/30 22:04:51 by jeff             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*utils_debug.c*/

#include "../../include/minishell.h"

void	print_token(t_token *token_list)
{
	int		i;
	t_token	*current;

	i = 0;
	current = token_list;
	while (current)
	{
		printf("token%d:, type: %s, value: %s\n",
			i, get_type_name(current->type), current->value);
		current = current->next;
		i++;
	}
}
