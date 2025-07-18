/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:57:44 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 01:58:45 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*read_user_input(t_data *data)
{
	char	*input;

	interactive_signal();
	input = readline(data->prompt);
	if (!input)
	{
		printf("exit\n");
		return (NULL);
	}
	return (input);
}

static void	handle_sigint_loop(t_data *data)
{
	if (g_signal == SIGINT)
	{
		data->exit_status = 130;
		g_signal = 0;
	}
}

static int	should_ignore_input(char *input)
{
	if (ft_strspn(input, NO_PRINTABLE) == ft_strlen(input))
		return (1);
	return (0);
}

static void	prepare_execution(char *input, t_data *data)
{
	data->input = gc_strdup(input, data->gc);
	tokenizer_list(data);
	expand_token_values(data);
	if (validate_syntax(data) == 0)
	{
		parse(data);
		exec_ast(data->tree, data);
	}
	gc_free(data->gc, data->input);
	delete_token_list(&data->token_list, data->gc);
}

void	loop(t_data *data)
{
	char	*input;

	while (42)
	{
		data->has_error = 0;
		input = read_user_input(data);
		if (!input)
			break ;
		handle_sigint_loop(data);
		if (should_ignore_input(input))
		{
			free(input);
			continue ;
		}
		if (*input && ft_strspn(input, NO_PRINTABLE) != ft_strlen(input))
			add_history(input);
		prepare_execution(input, data);
		free(input);
	}
}
