/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:39:12 by jemorais          #+#    #+#             */
/*   Updated: 2025/04/08 20:34:20 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*main.c*/

#include "../include/minishell.h"

int	main(int ac, char **av)
{
	t_data	*data;
	t_token	*tmp;

	if (ac == 2)
	{
		data = ft_calloc(1, sizeof(t_data));
		data->prompt = ft_strdup(av[1]);
		if (!data)
			return (1);
		tokenizer_list(data);
		tmp = data->token_list;
		while (tmp)
		{
			ft_printf("Token: [%s] - Tipo: %d\n", tmp->value, tmp->type);
			tmp = tmp->next;
		}
	}
	return (0);
}
