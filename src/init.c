/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:44:25 by jemorais          #+#    #+#             */
/*   Updated: 2025/06/10 15:45:00 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*init.c*/

#include "../include/minishell.h"

t_data	*init_data(char **ev)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_printf("Erro: in malloc\n");
		return (NULL);
	}
	ft_memset(data, 0, sizeof(t_data));
	data->env = ev;
	data->env_len = count_envlen(ev);
	data->prompt = "minishell$ ";
	return (data);
}