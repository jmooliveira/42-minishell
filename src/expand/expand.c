/* expand.c */

#include "../../include/minishell.h"

static bool	is_valid_var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static bool	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
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

static char	*get_var_expansion(const char *str, int *i, char **env, t_gc *gc)
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

static char	*expand_single_quotes(const char *str, int *i, t_data *data, char *result)
{
	char	*temp;

	(*i)++; // pular a aspa simples inicial
	while (str[*i] && str[*i] != '\'')
	{
		temp = normal_char(str, i, data->gc, result);
		result = temp;
	}
	if (str[*i] == '\'')
		(*i)++; // pular a aspa simples final
	return (result);
}

static char	*expand_variable(const char *str, int *i, t_data *data, char *result)
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
	temp = gc_strjoin(result, expansion, data->gc);
	gc_free(data->gc, result);
	return (temp);
}

static char	*append_quote_char(char *result, t_gc *gc)
{
	char	*temp;
	char	quote[2];

	quote[0] = '"';
	quote[1] = '\0';
	temp = gc_strjoin(result, quote, gc);
	gc_free(gc, result);
	return (temp);
}

static char	*process_double_quote_content(const char *str, int *i, t_data *data, char *result)
{
	char	*temp;

	(*i)++; // pular a aspa dupla abrindo

	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$' && str[*i + 1])
			result = expand_variable(str, i, data, result);
		else
		{
			temp = normal_char(str, i, data->gc, result);
			result = temp;
		}
	}

	return (result);
}

char	*expand_double_quotes(const char *str, int *i, t_data *data, char *result)
{
	result = append_quote_char(result, data->gc);
	result = process_double_quote_content(str, i, data, result);
	if (str[*i] == '"')
	{
		result = append_quote_char(result, data->gc);
		(*i)++;
	}
	return (result);
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
			result = expand_single_quotes(str, &i, data, result);
		else if (str[i] == '"')
			result = expand_double_quotes(str, &i, data, result);
		else if (str[i] == '$' && str[i + 1])
			result = expand_variable(str, &i, data, result);
		else
			result = normal_char(str, &i, data->gc, result);
	}
	return (result);
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

static void	trim_and_normalize_tokens(t_data *data)
{
	t_token	*token;
	char	*trimmed_val;

	token = data->token_list;
	while (token)
	{
		if (token->type == WORD || token->type == WORD_D || token->type == WORD_S)
		{
			trimmed_val = trim_quotes(token->value, data->gc);
			gc_free(data->gc, token->value);
			token->value = trimmed_val;
			token->type = WORD;
		}
		token = token->next;
	}
}

void	expand_token_values(t_data *data)
{
	expand_tokens(data);
	trim_and_normalize_tokens(data);
}
