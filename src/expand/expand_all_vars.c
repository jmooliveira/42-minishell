/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_all_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:23:39 by jemorais          #+#    #+#             */
/*   Updated: 2025/07/18 14:33:08 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*normal_char(const char *str, int *i, t_gc *gc, char *result)
{
	char	letter[2];
	char	*temp;

	letter[0] = str[*i];
	letter[1] = '\0';
	temp = gc_strjoin(result, letter, gc);
	gc_free(gc, result);
	(*i)++;
	return (temp);
}

char	*expand_variable(const char *str, int *i, t_data *data, char *res)
{
	char	*expansion;
	char	*temp;

	if (str[*i + 1] == '?')
	{
		expansion = gc_itoa(data->exit_status, data->gc);
		*i += 2;
	}
	else if (is_valid_var_start(str[*i + 1]))
	{
		(*i)++;
		expansion = get_var_expansion(str, i, data->env, data->gc);
	}
	else
	{
		expansion = gc_strdup("$", data->gc);
		(*i)++;
	}
	temp = gc_strjoin(res, expansion, data->gc);
	gc_free(data->gc, res);
	return (temp);
}

char	*expand_all_vars(const char *str, t_data *data)
{
	char	*result;
	int		i;

	result = gc_strdup("", data->gc);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			result = expand_s_quotes(str, &i, data, result);
		else if (str[i] == '"')
			result = expand_d_quotes(str, &i, data, result);
		else if (str[i] == '$' && str[i + 1])
			result = expand_variable(str, &i, data, result);
		else
			result = normal_char(str, &i, data->gc, result);
	}
	return (result);
}
