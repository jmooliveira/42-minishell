/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeff <jeff@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:48:47 by ancarol9          #+#    #+#             */
/*   Updated: 2025/06/12 19:11:23 by jeff             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*list_utils.c*/

#include "../../include/minishell.h"

t_token	*ft_token_last(t_token *lst)
{
	t_token	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}