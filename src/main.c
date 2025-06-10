/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:39:12 by jemorais          #+#    #+#             */
/*   Updated: 2025/06/10 15:45:43 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*main.c*/

#include "../include/minishell.h"

int	syntax_error(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	return (1);
}


int	check_pipe(t_token *list)
{
	if (list && list->type == PIPE)
		return(syntax_error("Error: pipe at begning"));
	while (list)
	{
		if (list->type == PIPE && (!list->next || list->next->type == PIPE))
			return(syntax_error("Error: invalid pipe"));
		list = list->next;
	}
	return (0);
}

// int	check_operator_sequence(t_token *list)
// {
// 	if (list && (list->type == AND || list->type == OR || list->type == REDIRECT_IN || list->type == REDIRECT_OUT || list->type == HEREDOC || list->type == APPEND))
// 		return (syntax_error("Error: invalid operator"));
// 	while (list)
// 	{
// 		if (list->type == AND || list->type == OR || list->type == REDIRECT_IN || list->type == REDIRECT_OUT || list->type == HEREDOC || list->type == APPEND)
// 		{
// 			if (!list->next || list->next->type)
// 		}
// 		list = list->next;
// 	}
// }


// void	validate_syntax(t_token *token_list)
// {
// 	// pipe no inicio e no fim
// 	if (check_pipe(token_list))
// 		return (1);
// 	// operadores duplicados ?
// 	// parenteses desbalanceados
// 	// parenteses mal posicionado
// 	// aspas nao fechadas
// 	// nada entre operadores
// 	// redirecionamento incompleto ?
// }

void	loop(t_data *data)
{
	char	*input;

	while (42)
	{
		input = readline(data->prompt);
		if (!input)
			break;
		if (*input) //se nao for um str vazia
			add_history(input); //ainda não implementado o histórico
		// Aqui você vai futuramente:
		data->input = ft_strdup(input);
		tokenizer_list(data);
		// func que libera a lista de token.!!!!
		// - verificar sintaxe
		// - construir árvore
		// - executar
		free(data->input);
		free(input);  // sempre liberar input
		delete_token_list(&data->token_list);
	}
}

int	count_envlen(char **ev)
{
	int len;

	len = 0;
	while (ev[len])
		len++;
	return (len);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Usage: ./minishell\n");
		return(1);
	}
	data = init_data(envp);
	if (!data)
		return (1);
	loop(data);
	// garbage_collector(&data);
	return (0);
}
