#include "../../include/minishell.h"

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