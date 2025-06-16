/*gc_utils.c*/

#include "../../include/minishell.h"

// vai para garbage_collector.c
t_gc	*gc_init(void)
{
	t_gc	*gc;

	gc = malloc(sizeof(t_gc));
	if (!gc)
		return (NULL);
	gc->head = NULL;
	return (gc);
}

void	gc_add(t_gc *gc, void *ptr)
{
	t_gc_node	*new_node;

	new_node = malloc(sizeof(t_gc_node));
	if (!new_node)
		return ;
	new_node->ptr = ptr;
	new_node->next = gc->head;
	gc->head = new_node;
}

void	*gc_malloc(t_gc *gc, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	gc_add(gc, ptr);
	return (ptr);
}

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

void	*gc_calloc(size_t nmemb, size_t size, t_gc *gc)
{
	unsigned char	*temp;
	size_t			total_size;
	size_t			i;

	total_size = nmemb * size;
	if (nmemb != 0 && (total_size / nmemb != size))
		return (NULL);
	temp = gc_malloc(gc, (nmemb * size));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < total_size)
		temp[i++] = 0;
	return (temp);
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
