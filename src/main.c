
/*main.c*/

#include "../include/minishell.h"

void	loop(t_data *data)
{
	char	*input;

	while (42)
	{
		input = readline(data->prompt);
		if (!input)
			break;

		if (*input)
			add_history(input);
		data->input = gc_strdup(input, data->gc);
		tokenizer_list(data);
		validate_syntax(data);
		// - construir árvore
		// - executar
		gc_free(data->gc, data->input);
		free(input);  // sempre liberar input
		delete_token_list(&data->token_list, data->gc);
	}
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
