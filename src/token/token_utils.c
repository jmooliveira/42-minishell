/*token_utils.c*/

#include "../../include/minishell.h"

t_token	*ft_token_last(t_token *lst)
{
	t_token	*last;

	if (!lst)
		return (NULL);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

int	skip_quotes(char *input, int start)
{
	char	quote;
	int		i;

	quote = input[start];
	i = start + 1;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] != quote)
		return (-1);
	return (i + 1);
}

char *trim_quotes(char *str, t_gc *gc)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	// Verifica se temos aspas delimitadoras do mesmo tipo no início e fim
	if (len >= 2)
	{
		// Caso: string delimitada por aspas duplas
		if (str[0] == '"' && str[len - 1] == '"')// Remove apenas as aspas duplas delimitadoras, preserva aspas simples internas
			return gc_substr(str, 1, len - 2, gc);
		// Caso: string delimitada por aspas simples
		else if (str[0] == '\'' && str[len - 1] == '\'') // Remove apenas as aspas simples delimitadoras, preserva aspas duplas internas
			return gc_substr(str, 1, len - 2, gc);
	}// Se não há aspas delimitadoras, remove todas as aspas (caso hello'world' ou hello""world)
	result = gc_malloc(gc, len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '"')
			i++;
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

void	delete_token_list(t_token **token_l, t_gc *gc)
{
	t_token	*tmp;

	while (*token_l)
	{
		tmp = (*token_l)->next;
		gc_free(gc, *token_l);
		*token_l = tmp;
	}
}

t_token	*new_token(char *value, t_type type, t_gc *gc)
{
	t_token	*token;

	token = gc_calloc(1, sizeof(t_token), gc);
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->expandable = false;
	token->next = NULL;
	return (token);
}
