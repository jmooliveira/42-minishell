/*validate_syntax.c*/

#include "../../include/minishell.h"

int	syntax_error(char *msg, t_data *data)
{
	ft_putstr_fd("Error: syntaxe error near ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	data->exit_status = 2;
	return (1);
}

int	is_logical_op(t_type type)
{
	return (type == PIPE || type == OR || type == AND);
}

int	is_redir(t_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC);
}

int	is_word(t_type type)
{
	return (type == WORD_D || type == WORD_S || type == WORD);
}

int	check_first_node(t_token *token_l)
{
	if (!token_l)
		return (1);
	if (is_logical_op(token_l->type) || token_l->type == PAR_CLOSE)
		return (1);
	if (token_l->type == HEREDOC)
		return (1);
	return (0);
}

int	check_last_node(t_token *token_l)
{
	t_token	*last;

	if (!token_l)
		return (1);
	last = ft_token_last(token_l);
	if (is_logical_op(last->type) || is_redir(last->type)
		|| last->type == PAR_OPEN)
		return (1);
	return (0);
}

int	check_invalid_op(t_token *token_l)
{
	t_token	*cur;

	if (!token_l)
		return (1);
	cur = token_l;
	while (cur)
	{
		if (cur->next)
		{
			if (is_logical_op(cur->type))
			{
				if (is_logical_op(cur->next->type))
					return (1);
			}
			else if (is_redir(cur->type))
			{
				if (is_redir(cur->next->type)
					|| is_logical_op(cur->next->type))
					return (1);
			}
		}
		cur = cur->next;
	}
	return (0);
}

int	check_unbalanced_quotes(t_token *tokens)
{
	t_token *cur = tokens;
	char quote = 0;

	while (cur)
	{
		char *s = cur->value;
		while (s && *s)
		{
			if (!quote && (*s == '\'' || *s == '"'))
				quote = *s; // abre aspas
			else if (quote && *s == quote)
				quote = 0; // fecha aspas
			s++;
		}
		cur = cur->next;
	}
	return (quote != 0); // 1 se alguma aspa ficou aberta
}


int	check_unbalanced_parentheses(t_token *token_list)
{
	int		balance;
	t_token	*cur;

	cur = token_list;
	balance = 0;
	while (cur)
	{
		if (cur->type == PAR_OPEN)
			balance++;
		else if (cur->type == PAR_CLOSE)
			balance--;
		if (balance < 0)
			return (1);
		cur = cur->next;
	}
	return (balance != 0);
}

int	check_empty_parentheses(t_token *token_l)
{
	t_token	*cur;

	cur = token_l;
	while (cur && cur->next)
	{
		if (cur->type == PAR_OPEN && cur->next->type == PAR_CLOSE)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	check_invalid_redir(t_token *token_l)
{
	t_token	*cur;

	cur = token_l;
	while (cur)
	{
		if (is_redir(cur->type))
		{
			if (!cur->next)
				return (1);
			if (!is_word(cur->next->type))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}

t_token	*find_subshell_end(t_token *start)
{
	t_token	*cur;
	int		balance;

	cur = start;
	balance = 1;
	while (cur)
	{
		if (cur->type == PAR_OPEN)
			balance++;
		else if (cur->type == PAR_CLOSE)
			balance--;
		if (balance == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

int	validate_subshell(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (check_last_node(tokens)
		|| check_first_node(tokens)
		|| check_invalid_op(tokens)
		|| check_unbalanced_parentheses(tokens)
		|| check_empty_parentheses(tokens)
		|| check_invalid_redir(tokens))
		return (1);
	return (0);
}

t_token	*get_token_before(t_token *list, t_token *target)
{
	t_token	*cur;

	cur = list;
	while (cur && cur->next != target)
		cur = cur->next;
	return (cur);
}

int	check_invalid_subshell_content(t_data *data)
{
	t_token	*cur;
	t_token	*end;
	t_token	*sub;
	t_token	*start;
	int		ret;

	cur = data->token_list;
	while (cur)
	{
		if (cur->type == PAR_OPEN)
		{
			start = cur->next;
			end = find_subshell_end(start);
			if (!end)
				return (1);
			end = get_token_before(data->token_list, end);
			sub = slice_tokens(start, end, data->gc);
			ret = validate_subshell(sub);
			if (ret)
				return (1);
			cur = end;
		}
		cur = cur->next;
	}
	return (0);
}

int	validate_syntax(t_data *data)
{
	// operador no inicio
	if (check_first_node(data->token_list))
		return (syntax_error("unexpected token", data));
	// operador no final
	else if (check_last_node(data->token_list))
		return (syntax_error("unexpected token", data));
	// operadores duplicados
	else if (check_invalid_op(data->token_list))
		return (syntax_error("unexpected token", data));
	// aspas desbalanceadas
	else if (check_unbalanced_quotes(data->token_list))
		return (syntax_error("unexpected token", data));
	// parenteses desbalanceados
	else if (check_unbalanced_parentheses(data->token_list))
		return (syntax_error("unexpected token", data));
	// parenteses vazio
	else if (check_empty_parentheses(data->token_list))
		return (syntax_error("empty parentheses", data));
	// redirecionamento incompleto (faltando o comando apos o redirecionamento)
	else if (check_invalid_redir(data->token_list))
		return (syntax_error("unexpected redirection", data));
	// parenteses com operadores invalidos.
	else if (check_invalid_subshell_content(data))
		return (syntax_error("unexpected token", data));
	return (0);
}


// TEM QUE TRATAR O BALANCEAMENTO DE ASPAS AQUI TAMBEM!!
