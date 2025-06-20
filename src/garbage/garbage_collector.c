/*garbage_collector.c*/

#include "../../include/minishell.h"

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

void	*gc_malloc(t_gc *gc, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	gc_add(gc, ptr);
	return (ptr);
}

t_gc	*gc_init(void)
{
	t_gc	*gc;

	gc = malloc(sizeof(t_gc));
	if (!gc)
		return (NULL);
	gc->head = NULL;
	return (gc);
}
