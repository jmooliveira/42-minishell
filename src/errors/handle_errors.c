/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:48:47 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/02 17:14:09 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*list_utils.c*/

#include "../../include/minishell.h"

// tirei de utils mas provavelmente deve voltar
int	syntax_error(char *msg, t_data *data)
{
	ft_putstr_fd("Error: syntax error near ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	data->exit_status = 2;
	return (1);
}
