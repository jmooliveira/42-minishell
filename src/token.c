/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:35:51 by jemorais          #+#    #+#             */
/*   Updated: 2025/04/08 18:36:34 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*token.c*/

#include "../include/minishell.h"

// bool	tokenizer_list(char *input, t_data *data);

bool	tokenizer_list(char *input, t_data *data)
{
	int i;

	i = 0;
	(void)data;
	while (ft_strchr(NO_PRINTABLE, input[i]) && input[i] != '\0')
		i++;
	i--;
	while (input[i])
	{

	}
	return (true);
}

