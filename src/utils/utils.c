/*utils.c*/

#include "../../include/minishell.h"

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
