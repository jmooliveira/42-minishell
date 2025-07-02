/*token.c*/

#include "../../include/minishell.h"

// void	add_token_to_list(t_data *data, char *token_def, t_type id_token)
// {
// 	t_token	*new;
// 	t_token	*tmp;
// 	// char	*clean_value;

// 	// clean_value = trim_quotes(token_def, data->gc);
// 	new = new_token(token_def, id_token, data->gc);
// 	if (!new)
// 		return ;
// 	new->expandable = (id_token == WORD || id_token == WORD_D);
// 	// marca true quando tem que expandir uma variavel
// 	if (!data->token_list)
// 	{
// 		data->token_list = new;
// 		return ;
// 	}
// // <<<<<<< HEAD
// 	tmp = data->token_list;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = new;
// // =======
// 	// print_token(data->token_list); //DEBUG
// 	// return (i);
// // >>>>>>> feature/build-ast
// }

int	give_id(char *token_def)
{
	if (!ft_strncmp(token_def, "|", 1) && token_def[1] == '\0')
		return (PIPE);
	if (!ft_strncmp(token_def, "&&", 2) && token_def[2] == '\0')
		return (AND);
	if (!ft_strncmp(token_def, "||", 2) && token_def[2] == '\0')
		return (OR);
	if (!ft_strncmp(token_def, "(", 1) && token_def[1] == '\0')
		return (PAR_OPEN);
	if (!ft_strncmp(token_def, ")", 1) && token_def[1] == '\0')
		return (PAR_CLOSE);
	if (!ft_strncmp(token_def, "<", 1) && token_def[1] == '\0')
		return (REDIR_IN);
	if (!ft_strncmp(token_def, ">", 1) && token_def[1] == '\0')
		return (REDIR_OUT);
	if (!ft_strncmp(token_def, ">>", 2) && token_def[2] == '\0')
		return (APPEND);
	if (!ft_strncmp(token_def, "<<", 2) && token_def[2] == '\0')
		return (HEREDOC);
	if (ft_strchr(token_def, '=') && token_def[0] != '=')
		return (ASSIGNMENT);
	if (token_def[0] == '\'' && token_def[ft_strlen(token_def) - 1] == '\'')
		return (WORD_S);
	if (token_def[0] == '"' && token_def[ft_strlen(token_def) - 1] == '"')
		return (WORD_D);
	return (WORD);
}

int	find_token_end(char *inpt, int start)
{
	int	end;
	int	quote_end;

	if (ft_strchr("|&<>()", inpt[start]))
	{
		if ((inpt[start] == inpt[start + 1]) && ft_strchr("|&<>", inpt[start]))
			return (start + 2);
		return (start + 1);
	}
	end = start;
	while (inpt[end] && !ft_strchr(" \t\n|&<>()", inpt[end]))
	{
		if (inpt[end] == '\'' || inpt[end] == '"')
		{
			quote_end = skip_quotes(inpt, end);
			if (quote_end == -1)
				return (-1); // aspa não fechada
			end = quote_end;
		}
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
	if (end == -1)
	{
		syntax_error("unclosed quote", data);
		return (ft_strlen(data->input)); // força a parada da tokenização
	}
	token_def = gc_substr(data->input, start, end - start, data->gc);
	id_token = give_id(token_def);
	add_token_to_list(data, token_def, id_token);
	return (end);
}

// t_token	*new_token(char *value, t_type type, t_gc *gc)
// {
// 	t_token	*token;

// 	token = gc_calloc(1, sizeof(t_token), gc);
// 	if (!token)
// 		return (NULL);
// 	token->value = value;
// 	token->type = type;
// 	token->expandable = false;
// 	token->next = NULL;
// 	return (token);
// }

void	add_token_to_list(t_data *data, char *token_def, t_type id_token)
{
	t_token	*new;
	t_token	*tmp;
	char	*clean_value;

	if (id_token == WORD_S || id_token == WORD_D)
		clean_value = trim_quotes(token_def, data->gc);
	else
		clean_value = gc_strdup(token_def, data->gc);
	new = new_token(clean_value, id_token, data->gc);
	if (!new)
		return ;
	if (id_token == WORD_D || id_token == WORD)
		new->expandable = true;
	else
		new->expandable = false;
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

int	tokenizer_list(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		while (data->input[i] && ft_strchr(NO_PRINTABLE, data->input[i]))
			i++;
		if (data->input[i])
			i = get_token(data, i);
	}
	print_token(data->token_list); //DEBUG
	return (i);
}