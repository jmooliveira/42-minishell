/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeff <jeff@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:48:47 by ancarol9          #+#    #+#             */
/*   Updated: 2025/06/20 17:33:14 by jeff             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*list_utils.c*/

#include "../../include/minishell.h"

// tirei de utils mas provavelmente deve voltar
int	syntax_error(char *msg, t_data *data)
{
	ft_putstr_fd("Error: syntaxe error near ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	data->exit_status = 2;
	return (1);
}
