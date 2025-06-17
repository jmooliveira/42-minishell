/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:39:12 by jemorais          #+#    #+#             */
/*   Updated: 2025/06/10 16:54:58 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*main.c*/

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Usage: ./minishell\n");
		return(1);
	}
	data = init_data(envp);
	if (!data)
		return (1);
	loop(data);
	rl_clear_history();
	gc_clear(data->gc);
	return (0);
}
