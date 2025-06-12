/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeff <jeff@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:34:09 by ancarol9          #+#    #+#             */
/*   Updated: 2025/06/12 19:10:52 by jeff             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*init.c*/

#include "../../include/minishell.h"

int	count_envlen(char **ev)
{
	int len;

	len = 0;
	while (ev[len])
		len++;
	return (len);
}

t_data	*init_data(char **ev)
{
	t_data	*data;
	t_gc	*gc;
	
	gc = gc_init();
	data = gc_malloc(gc, sizeof(t_data));
	if (!data)
	{
		ft_printf("Erro: in malloc\n");
		return (NULL);
	}
	ft_memset(data, 0, sizeof(t_data));
	data->env = ev;
	data->env_len = count_envlen(ev);
	data->prompt = "minishell$ ";
	data->gc = gc;
	return (data);
}