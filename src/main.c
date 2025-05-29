/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:39:12 by jemorais          #+#    #+#             */
/*   Updated: 2025/05/29 19:18:11 by ancarol9         ###   ########.fr       */
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


// int	validate_syntax(t_token *token_list)
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


void	delete_token_list(t_token **token_l, t_gc *gc)
{
	t_token	*tmp;

	while(*token_l)
	{
		tmp = (*token_l)->next;
		gc_free(gc, *token_l);
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
		if (*input) //se nao for um str vazia, nao sei se tem que ver white spaces
			add_history(input);

		// Aqui você vai futuramente:
		data->input = gc_strdup(input, data->gc);
		tokenizer_list(data);
		// - verificar sintaxe
		// - construir árvore
		// - executar
		gc_free(data->gc, data->input);
		free(input);  // sempre liberar input
		delete_token_list(&data->token_list, data->gc);
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
	t_gc	*gc;
	
	gc = gc_init();
	data = gc_malloc(gc, sizeof(t_data));
	if (!data)
	{
		ft_printf("Erro: in malloc\n");
		return (NULL);
	}
	ft_memset(data, 0, sizeof(t_data));
	data->env = ev;
	data->env_len = count_envlen(ev);
	data->prompt = "minishell$ ";
	data->gc = gc;
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
	rl_clear_history();
	gc_clear(data->gc);
	return (0);
}
