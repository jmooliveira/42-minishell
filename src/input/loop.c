/*loop.c*/

#include "../../include/minishell.h"

void	loop(t_data *data)
{
	char	*input;

	while (42)
	{
		input = readline(data->prompt);
		if (!input)
			break ;
		if (*input && ft_strspn(input, NO_PRINTABLE) != ft_strlen(input))
		// se nao for um str vazia, nao sei se tem que ver white spaces
			add_history(input);
		data->input = gc_strdup(input, data->gc);
		tokenizer_list(data);
		expand_token_values(data);
		validate_syntax(data);
		// - construir árvore
		// - executar
		gc_free(data->gc, data->input);
		free(input); // sempre liberar input
		delete_token_list(&data->token_list, data->gc);
	}
}
