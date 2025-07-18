/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_trim_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 02:01:53 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 02:02:24 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*remove_wrapping_quotes(char *str, t_gc *gc)
{
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2)
	{
		if ((str[0] == '"' && str[len - 1] == '"')
			|| (str[0] == '\'' && str[len - 1] == '\''))
			return (gc_substr(str, 1, len - 2, gc));
	}
	return (NULL);
}

static char	*remove_inner_quotes(char *str, t_gc *gc)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*result;

	len = ft_strlen(str);
	result = gc_malloc(gc, len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] != '\'' && str[i] != '"')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*trim_quotes(char *str, t_gc *gc)
{
	char	*trimmed;

	trimmed = remove_wrapping_quotes(str, gc);
	if (trimmed)
		return (trimmed);
	return (remove_inner_quotes(str, gc));
}
