/*loop.c*/

#include "../../include/minishell.h"

void	loop(t_data *data)
{
	char	*input;

	while (42)
	{
		interactive_signal();
		// tem que limpar os arquivos do heredoc nesse ponto tambem, talvez nao?
		input = readline(data->prompt);
		if (!input)
			break ;
		if (*input && ft_strspn(input, NO_PRINTABLE) != ft_strlen(input))
			add_history(input);
		data->input = gc_strdup(input, data->gc);
		tokenizer_list(data);
		expand_token_values(data);
		if (validate_syntax(data) == 0)
		{
			parse(data);
			exec_ast(data->tree ,data);
		}
		gc_free(data->gc, data->input);
		free(input);
		delete_token_list(&data->token_list, data->gc);
	}
}
