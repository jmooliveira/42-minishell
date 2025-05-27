/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:39:12 by jemorais          #+#    #+#             */
/*   Updated: 2025/05/27 19:35:14 by ancarol9         ###   ########.fr       */
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


int	validate_pipe(t_token *list)
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

int	validate


void	validate_syntax(t_token *token_list)
{
	// pipe no inicio e no fim
	if (validate_pipe(token_list))
		return (1);
	// operadores duplicados ?
	// parenteses desbalanceados
	// parenteses mal posicionado
	// aspas nao fechadas
	// nada entre operadores
	// redirecionamento incompleto ?
}


void	delete_token_list(t_token **token_l)
{
	t_token	*tmp;

	while(*token_l)
	{
		tmp = (*token_l)->next;
		free(*token_l);
		*token_l = tmp;
	}
}

void	loop(t_data *data)
{
	char	*input;

	while (42)
	{
		input = readline(data->prompt);
		if (!input)
			break;
		if (*input) //se nao for um str vazia
			add_history(input);

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

t_data	*init_data(char **ev)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_printf("Erro: in malloc\n");
		return (NULL);
	}
	ft_memset(data, 0, sizeof(t_data));
	data->env = ev;
	data->env_len = count_envlen(ev);
	data->prompt = "minishell$ ";
	return (data);
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
