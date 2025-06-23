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
		if (*input && ft_strspn(input, NO_PRINTABLE) != ft_strlen(input)) //se nao for um str vazia, nao sei se tem que ver white spaces
			add_history(input);
		data->input = gc_strdup(input, data->gc);
		tokenizer_list(data);
		print_token(data->token_list);
		expand_token_values(data);
		if (!validate_syntax(data))
		{
			parse(data);
			// - executar
		}
		gc_free(data->gc, data->input);
		free(input); // sempre liberar input
		delete_token_list(&data->token_list, data->gc);
	}
}

// adicionada para pular espaços iniciais
size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strchr(accept, s[i]))
			break ;
		i++;
	}
	return (i);
}
