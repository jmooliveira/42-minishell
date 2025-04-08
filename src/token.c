/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:35:51 by jemorais          #+#    #+#             */
/*   Updated: 2025/04/08 20:39:02 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*token.c*/

#include "../include/minishell.h"

int	tokenizer_list(t_data *data)
{
	int	i;

	i = 0;
	while (ft_strchr(NO_PRINTABLE, data->prompt[i]) && data->prompt[i])
		i++;
	while (data->prompt[i])
	{
		if (!ft_strchr(NO_PRINTABLE, data->prompt[i]) && data->prompt[i])
			i = get_token(data, i);
		else
			i++;
	}
	return (i);
}

int	get_token(t_data *data, int start)
{
	int				end;
	char			*token_def;
	t_token_type	id_token;

	end = start;
	while (!ft_strchr(NO_PRINTABLE, data->prompt[end]) && data->prompt[end])
		end++;
	token_def = ft_substr(data->prompt, start, end - start);
	id_token = give_id(token_def);
	add_token_to_list(data, token_def, id_token);
	return (end);
}

int	give_id(char *token_def)
{
	if (!ft_strncmp(token_def, "|", 1))
		return (PIPE);
	if (!ft_strncmp(token_def, "<", 1))
		return (REDIRECT_IN);
	if (!ft_strncmp(token_def, ">", 1))
		return (REDIRECT_OUT);
	if (!ft_strncmp(token_def, ">>", 2))
		return (APPEND);
	if (!ft_strncmp(token_def, "<<", 2))
		return (HEREDOC);
	return (WORD);
}

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token_to_list(t_data *data, char *token_def, t_token_type id_token)
{
	t_token	*new;
	t_token	*tmp;

	new = new_token(token_def, id_token);
	if (!new)
		return ;
	if (!data->token_list)
	{
		data->token_list = new;
		return ;
	}
	tmp = data->token_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
