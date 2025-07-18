/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:56:51 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 01:56:52 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
