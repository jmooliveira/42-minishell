/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:23:45 by jemorais          #+#    #+#             */
/*   Updated: 2025/07/18 14:26:53 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_valid_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
