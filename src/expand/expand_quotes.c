/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:23:53 by jemorais          #+#    #+#             */
/*   Updated: 2025/07/18 14:31:25 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	trim_and_normalize_tokens(t_data *data)
{
	t_token	*token;
	char	*trimmed_val;

	token = data->token_list;
	while (token)
	{
		if (token->type == WORD || token->type == WORD_D
			|| token->type == WORD_S)
		{
			trimmed_val = trim_quotes(token->value, data->gc);
			gc_free(data->gc, token->value);
			token->value = trimmed_val;
			token->type = WORD;
		}
		token = token->next;
	}
}

char	*expand_s_quotes(const char *str, int *i, t_data *data, char *res)
{
	char	*temp;

	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		temp = normal_char(str, i, data->gc, res);
		res = temp;
	}
	if (str[*i] == '\'')
		(*i)++;
	return (res);
}

char	*append_quote_char(char *result, t_gc *gc)
{
	char	*temp;
	char	quote[2];

	quote[0] = '"';
	quote[1] = '\0';
	temp = gc_strjoin(result, quote, gc);
	gc_free(gc, result);
	return (temp);
}

char	*proc_d_quote_content(const char *str, int *i, t_data *data, char *res)
{
	char	*temp;

	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$' && str[*i + 1])
			res = expand_variable(str, i, data, res);
		else
		{
			temp = normal_char(str, i, data->gc, res);
			res = temp;
		}
	}
	return (res);
}

char	*expand_d_quotes(const char *str, int *i, t_data *data, char *res)
{
	res = append_quote_char(res, data->gc);
	res = proc_d_quote_content(str, i, data, res);
	if (str[*i] == '"')
	{
		res = append_quote_char(res, data->gc);
		(*i)++;
	}
	return (res);
}
