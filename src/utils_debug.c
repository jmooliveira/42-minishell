/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:43:22 by ancarol9          #+#    #+#             */
/*   Updated: 2025/05/28 17:25:32 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


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