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

char	*expand_all_vars(const char *str, char **env, t_gc *gc)
{
	char	*result;
	char	*temp;
	int		i;
	int		start;
	char	*var_name;
	char	*env_value;
	char	*value;
	char	letter[2];

	result = gc_strdup("", gc);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			start = ++i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			var_name = gc_substr(str, start, i - start, gc);
			env_value = get_env_value(var_name, env);
			value = NULL;
			if (env_value)
				value = gc_strdup(env_value, gc);
			else
				value = gc_strdup("", gc);
			temp = gc_strjoin(result, value, gc);
			gc_free(gc, result);
			result = temp;
		}
		else
		{
			letter[0] = str[i];
			letter[1] = '\0';
			temp = gc_strjoin(result, letter, gc);
			gc_free(gc, result);
			result = temp;
			i++;
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
			expanded_value = expand_all_vars(token->value, data->env, data->gc);
			gc_free(data->gc, token->value);
			token->value = expanded_value;
		}
		token = token->next;
	}
}

// jogar essa funcao para gc_utils.c
char	*gc_strjoin(char *s1, char *s2, t_gc *gc)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (!joined)
		return (NULL);
	gc_add(gc, joined);
	return (joined);
}
