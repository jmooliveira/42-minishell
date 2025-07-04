/*gc_utils.c*/

#include "../../include/minishell.h"

void	gc_clear(t_gc *gc)
{
	t_gc_node	*tmp;

	while (gc && gc->head)
	{
		tmp = gc->head->next;
		if (gc->head->ptr)
			free(gc->head->ptr);
		free(gc->head);
		gc->head = tmp;
	}
	if (gc)
		free(gc);
}

void	gc_free(t_gc *gc, void *ptr)
{
	t_gc_node	*cur;
	t_gc_node	*prev;

	cur = gc->head;
	prev = NULL;
	while (cur)
	{
		if (cur->ptr == ptr)
		{
			if (prev)
				prev->next = cur->next;
			else
				gc->head = cur->next;
			free(cur->ptr);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

char	*gc_strdup(const char *s, t_gc *gc)
{
	size_t	len;
	char	*dup;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = gc_malloc(gc, len + 1);
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}

char	*gc_substr(char const *s, unsigned int start, size_t len, t_gc *gc)
{
	char		*substr;
	size_t		i;

	if (!s)
		return (NULL);
	else if (start > ft_strlen(s))
		return (gc_strdup("", gc));
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = (char *) gc_calloc((len + 1), sizeof(char), gc);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*gc_strjoin(char *s1, char *s2, t_gc *gc)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (!joined)
		return (NULL);
	gc_add(gc, joined);
	return (joined);
}

static unsigned int	ft_nbr_digit(int n) // as tres abaixo são utilizadas na gc_itoa
{
	unsigned int	count;
	unsigned int	nb;

	count = 1;
	nb = (n < 0) ? -n : n;
	while (nb >= 10)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

static void	ft_at(char *str, unsigned int digits, unsigned int n)
{
	str[digits] = '\0';
	while (digits-- > 0)
	{
		str[digits] = (n % 10) + '0';
		n /= 10;
	}
}

char	*gc_itoa(int n, t_gc *gc)
{
	char			*nbr;
	unsigned int	nbr_digits;
	unsigned int	nbr_number;

	nbr_digits = ft_nbr_digit(n);
	if (n < 0)
	{
		nbr_digits++;
		nbr = gc_calloc(nbr_digits + 1, sizeof(char), gc);
		if (!nbr)
			return (NULL);
		nbr_number = -n;
		ft_at(nbr, nbr_digits, nbr_number);
		nbr[0] = '-';
	}
	else
	{
		nbr = gc_calloc(nbr_digits + 1, sizeof(char), gc);
		if (!nbr)
			return (NULL);
		ft_at(nbr, nbr_digits, n);
	}
	return (nbr);
}
