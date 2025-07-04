/*expand.c*/

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

static char	*get_var_expansion(const char *str, int *i, char **env, t_gc *gc)
{
	int		start;
	char	*var_name;
	char	*env_value;
	char	*value;

	if (str[*i] == '{') // ${VAR}
	{
		start = ++(*i);
		while (str[*i] && str[*i] != '}')
			(*i)++;
		if (str[*i] != '}')
			return (gc_strdup("", gc)); // não encontrou fechamento
		var_name = gc_substr(str, start, *i - start, gc);
		(*i)++; // pula '}'
	}
	else // $VAR
	{
		start = *i;
		while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
			(*i)++;
		var_name = gc_substr(str, start, *i - start, gc);
	}
	env_value = get_env_value(var_name, env);
	if (env_value)
		value = gc_strdup(env_value, gc);
	else
		value = gc_strdup("", gc);
	return (value);
}

static char	*normal_char(const char *str, int *i, t_gc *gc, char *result)
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

char	*expand_all_vars(const char *str, char **env, t_gc *gc, t_data *data)
{
	char	*result;
	char	*temp;
	char	*expansion;
	int		i;

	result = gc_strdup("", gc);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]) // caso especial
		{
			if (str[i+1] == '?')
			{
				expansion = gc_itoa(data->exit_status, gc);
				i += 2;
			}
			else if (str[i + 1] == '{') 
			{
				i++;
				expansion = get_var_expansion(str, &i, env, gc);
			}
			else
			{
				i++;
				expansion = get_var_expansion(str, &i, env, gc);
			}
			temp = gc_strjoin(result, expansion, gc);
			gc_free(gc, result);
			result = temp;
		}
		else
		{
			temp = normal_char(str, &i, gc, result);
			result = temp;
		}
	}
	return (result);
}

void	expand_token_values(t_data *data)
{
	t_token	*token;
	char	*expanded_value;

	token = data->token_list;
	while (token)
	{
		if (token->expandable && (token->type == WORD || token->type == WORD_D))
		{
			expanded_value = expand_all_vars(token->value, data->env, data->gc, data);
			gc_free(data->gc, token->value);
			token->value = expanded_value;
		}
		token = token->next;
	}
}
