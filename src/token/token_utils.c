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
    size_t len;
    char *result;
    size_t i, j;
    bool has_adjacent_quotes = false;

    if (!str)
        return (NULL);
        
    len = ft_strlen(str);
    if (len < 2)
        return gc_strdup(str, gc);
    
    // Verifica se há aspas adjacentes (como em hello'world')
    for (i = 0; i < len - 1; i++) {
        if ((str[i] == '\'' || str[i] == '"') && 
            i > 0 && i < len - 1 && 
            str[i-1] != ' ' && str[i+1] != ' ') {
            has_adjacent_quotes = true;
            break;
        }
    }
    
    // Se tiver aspas adjacentes, remove todas as aspas
    if (has_adjacent_quotes) {
        result = gc_malloc(gc, len + 1);
        if (!result)
            return (NULL);
        
        i = 0;
        j = 0;
        while (i < len) {
            if (str[i] != '\'' && str[i] != '"')
                result[j++] = str[i];
            i++;
        }
        result[j] = '\0';
        return result;
    }
    
    // Remove apenas as aspas externas do mesmo tipo
    if ((str[0] == '\'' && str[len - 1] == '\'') || 
        (str[0] == '"' && str[len - 1] == '"'))
        return gc_substr(str, 1, len - 2, gc);
    
    return gc_strdup(str, gc);
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
	token->is_builtin = is_builtin(value);
	return (token);
}
