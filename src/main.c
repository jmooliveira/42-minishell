/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:39:12 by jemorais          #+#    #+#             */
/*   Updated: 2025/04/08 18:52:47 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*main.c*/

#include "../include/minishell.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		data = ft_calloc(1, sizeof(t_data));
		if (!data)
			return (1);
		tokenizer_list(av[1], data);

		t_token	*tmp = data->token_list;
		while (tmp)
		{
			ft_printf("[%s]\n", tmp->value);
			tmp = tmp->next;
		}
	}
	return (0);
}
