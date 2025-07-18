/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:23:26 by jemorais          #+#    #+#             */
/*   Updated: 2025/07/18 14:28:16 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env_value(const char *var_name, char **env)
{
	size_t	var_len;
	int		i;

	if (!var_name || !env)
		return (NULL);
	var_len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, var_len)
			== 0 && env[i][var_len] == '=')
			return (env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}

static char	*extract_var_name(const char *str, int *i, t_gc *gc)
{
	int		start;
	char	*var_name;

	if (str[*i] == '{')
	{
		start = ++(*i);
		while (str[*i] && str[*i] != '}')
			(*i)++;
		if (str[*i] != '}')
			return (gc_strdup("", gc));
		var_name = gc_substr(str, start, *i - start, gc);
		(*i)++;
	}
	else
	{
		start = *i;
		while (str[*i] && is_valid_var_char(str[*i]))
			(*i)++;
		var_name = gc_substr(str, start, *i - start, gc);
	}
	return (var_name);
}

char	*get_var_expansion(const char *str, int *i, char **env, t_gc *gc)
{
	char	*var_name;
	char	*env_value;
	char	*value;

	var_name = extract_var_name(str, i, gc);
	env_value = get_env_value(var_name, env);
	if (env_value)
		value = gc_strdup(env_value, gc);
	else
		value = gc_strdup("", gc);
	return (value);
}

static void	expand_tokens(t_data *data)
{
	t_token	*token;
	t_token	*prev;
	char	*exp_val;

	token = data->token_list;
	prev = NULL;
	while (token)
	{
		if (token->expandable && (token->type == WORD || token->type == WORD_D))
		{
			exp_val = expand_all_vars(token->value, data);
			gc_free(data->gc, token->value);
			token->value = exp_val;
			if (token->value[0] == '\0' && !prev)
			{
				data->token_list = token->next;
				token = data->token_list;
				continue ;
			}
		}
		prev = token;
		token = token->next;
	}
}

void	expand_token_values(t_data *data)
{
	expand_tokens(data);
	trim_and_normalize_tokens(data);
}
