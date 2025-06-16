/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:43:22 by ancarol9          #+#    #+#             */
/*   Updated: 2025/06/16 16:40:35 by jemorais         ###   ########.fr       */
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
		printf("token%d:, id: %d, value: %s\n",
			i, current->type, current->value);
		current = current->next;
		i++;
	}
}
