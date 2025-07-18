/*expand.c*/

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
		if (ft_strncmp(env[i], var_name, var_len)
			== 0 && env[i][var_len] == '=')
			return (env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}

static char	*extract_braced_var(const char *str, int *i, t_gc *gc)
{
	int		start;
	char	*var_name;

	start = ++(*i);
	while (str[*i] && str[*i] != '}')
		(*i)++;
	if (str[*i] != '}')
		return (gc_strdup("", gc));
	var_name = gc_substr(str, start, *i - start, gc);
	(*i)++;
	return (var_name);
}

static char	*get_var_expansion(const char *str, int *i, char **env, t_gc *gc)
{
	int		start;
	char	*var_name;
	char	*env_value;
	char	*value;

	if (str[*i] == '{')
		var_name = extract_braced_var(str, i, gc);
	else
	{
		start = *i;
		while (str[*i] && is_valid_var_char(str[*i]))
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

// _semi refatorado_______________________________________________________________________________________________________________________________

static char *handle_variable(const char *str, int *i, t_data *data)
{
    char    *expansion;

    if (str[*i + 1] == '?')
    {
        expansion = gc_itoa(data->exit_status, data->gc);
        *i += 2;
    }
    else if (str[*i + 1] == '{' || is_valid_var_start(str[*i + 1]))
    {
        (*i)++;
        expansion = get_var_expansion(str, i, data->env, data->gc);
    }
    else
    {
        expansion = gc_strdup("$", data->gc);
        (*i)++;
    }
    return (expansion);
}

// PROBLEMA COM MUITOS PARAMETROS
static char *handle_quotes(const char *str, int *i, t_gc *gc, char *result,
    bool *in_single, bool *in_double)
{
    char    *temp;

    temp = NULL;
    if (str[*i] == '\'' && !(*in_double))
    {
        *in_single = !(*in_single);
        temp = normal_char(str, i, gc, result);
    }
    else if (str[*i] == '"' && !(*in_single))
    {
        *in_double = !(*in_double);
        temp = normal_char(str, i, gc, result);
    }
    return (temp);
}

static char *process_char_in_expand(const char *str, int *i, t_data *data,
	char *result, bool *in_single, bool *in_double)
{
    char    *temp;
    char    *expansion;

    temp = handle_quotes(str, i, data->gc, result, in_single, in_double);
    if (temp)
        return (temp);
    if (str[*i] == '$' && !(*in_single) && str[*i + 1])
    {
        expansion = handle_variable(str, i, data);
        temp = gc_strjoin(result, expansion, data->gc);
        return (temp);
    }
    else
    {
        temp = normal_char(str, i, data->gc, result);
        return (temp);
    }
}

char    *expand_all_vars(const char *str, t_data *data)
{
    char    *result;
    char    *temp;
    int     i;
    bool    in_single;
    bool    in_double;

    result = gc_strdup("", data->gc);
    i = 0;
    in_single = false;
    in_double = false;
    while (str[i])
    {
        temp = process_char_in_expand(str, &i, data, result, &in_single, &in_double);
        gc_free(data->gc, result);
        result = temp;
    }
    return (result);
}

static void handle_token_expansion(t_token *token, t_data *data)
{
    char    *exp_val;

    exp_val = expand_all_vars(token->value, data);
    gc_free(data->gc, token->value);
    token->value = exp_val;
}

static void handle_token_trimming(t_token *token, t_data *data)
{
    char    *trimmed_val;

    trimmed_val = trim_quotes(token->value, data->gc);
    gc_free(data->gc, token->value);
    token->value = trimmed_val;
    token->type = WORD;
}

void    expand_token_values(t_data *data)
{
    t_token *token;
    t_token *prev;

    token = data->token_list;
    prev = NULL;
    while (token)
    {
        if (token->expandable && (token->type == WORD || token->type == WORD_D))
        {
            handle_token_expansion(token, data);
            if (token->value[0] == '\0' && !prev)
            {
                data->token_list = token->next;
                token = data->token_list;
                continue ;
            }
        }
        if (is_word(token->type))
        {
            handle_token_trimming(token, data);
        }
        prev = token;
        token = token->next;
    }
}

