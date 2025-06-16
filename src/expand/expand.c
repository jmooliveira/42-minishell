/*expand.c*/

#include "../../include/minishell.h"

char	*expand_all_vars(const char *str, char **env, t_gc *gc)
{
	char	*result;
	char	*temp;
	size_t	i;

	result = gc_strdup("", gc);
	i = 0;
	while (str[i])
    {
        if (str[i] == '$' && str[i + 1] && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
        {
            size_t start = ++i;
            while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
                i++;
            char *var_name = gc_substr(str, start, i - start, gc);
            char *env_value = get_env_value(var_name, env);
            char *value = env_value ? gc_strdup(env_value, gc) : gc_strdup("", gc);
            temp = gc_strjoin(result, value, gc);
            gc_free(gc, result);
            result = temp;
            // gc_free(gc, var_name); var_name já foi alocado com gc_malloc, não precisa liberar manualmente
		}
		else
		{
			char	letter[2] = {str[i], 0};
			temp = gc_strjoin(result, letter, gc);
			gc_free(gc, result);
			result = temp;
			i++;
		}
	}
	return (result);
}

void    expand_token_values(t_data *data)
{
	t_token *token;

	token = data->token_list;
	while (token)
	{
		if (token->expandable && (token->type == WORD || token->type == WORD_D))
		{
			char *expanded_value = expand_all_vars(token->value, data->env, data->gc);
			gc_free(data->gc, token->value);
			token->value = expanded_value;
		}
		token = token->next;
	}
}

char *gc_strjoin(char *s1, char *s2, t_gc *gc)
{
	char *joined = ft_strjoin(s1, s2);
	if (!joined)
		return (NULL);
	gc_add(gc, joined);
	return (joined);
}

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
		if (ft_strncmp(env[i], var_name, var_len) == 0 && env[i][var_len] == '=')
			return (env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}
