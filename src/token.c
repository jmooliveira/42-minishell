/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:35:51 by jemorais          #+#    #+#             */
/*   Updated: 2025/05/27 18:10:19 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*token.c*/

#include "../include/minishell.h"


int	tokenizer_list(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		while (ft_strchr(NO_PRINTABLE, data->input[i]))
			i++;
		if (data->input[i])
			i = get_token(data, i);
	}
	print_token(data->token_list);			//DEBUG
	return (i);
}

int	skip_quotes(char *input, int start)
{
	char	quote;
	int		i;

	quote = input[start];
	i = start + 1;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
		i++;
	return (i);
	// TODO: Implementar leitura contínua (prompt secundário) para aspas não fechadas,
	// assim como o comportamento do bash:
	// Exemplo:
	// minishell$ echo "oi
	// > tudo bem"
	// Isso deve juntar as linhas até encontrar a aspa final.
	// Por enquanto, a função apenas detecta erro de aspas não fechadas.
}

int	find_token_end(char *input, int start)
{
	int end;

	if (ft_strchr("|&<>()", input[start]))
	{
		if ((input[start] == input[start + 1]) && ft_strchr("|&<>", input[start]))
			return (start + 2);
		return(start + 1);
	}
	end = start;
	while (input[end] && !ft_strchr(" \t\n|&<>()", input[end]))
	{
		if (input[end] == '\'' || input[end] == '"')
			end = skip_quotes(input, end);
		else
			end++;
	}
	return (end);
}

int	get_token(t_data *data, int start)
{
	int				end;
	char			*token_def;
	t_type			id_token;

	end = find_token_end(data->input, start);					
	token_def = ft_substr(data->input, start, end - start);
	id_token = give_id(token_def);
	add_token_to_list(data, token_def, id_token);
	return (end);
}

int	give_id(char *token_def)
{
	if (!ft_strncmp(token_def, "|", 1) && token_def[1] == '\0')
		return (PIPE);
	if (!ft_strncmp(token_def, "&&", 2) && token_def[2] == '\0')
		return (AND);
	if (!ft_strncmp(token_def, "||", 2)  && token_def[2] == '\0')
		return (OR);
	if (!ft_strncmp(token_def, "(", 1) && token_def[1] == '\0')
		return (PARENT_OPEN);
	if (!ft_strncmp(token_def, ")", 1) && token_def[1] == '\0')
		return (PARENT_CLOSE);
	if (!ft_strncmp(token_def, "<", 1) && token_def[1] == '\0')
		return (REDIRECT_IN);
	if (!ft_strncmp(token_def, ">", 1) && token_def[1] == '\0')
		return (REDIRECT_OUT);
	if (!ft_strncmp(token_def, ">>", 2) && token_def[2] == '\0')
		return (APPEND);
	if (!ft_strncmp(token_def, "<<", 2) && token_def[2] == '\0')
		return (HEREDOC);
	if (ft_strchr(token_def, '=') && token_def[0] != '=')
		return (ASSIGNMENT);
	return (ARG);
}

t_token	*new_token(char *value, t_type type)
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

void	add_token_to_list(t_data *data, char *token_def, t_type id_token)
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
	else
	{
		tmp = data->token_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

