/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:44:01 by ancarol9          #+#    #+#             */
/*   Updated: 2025/05/28 20:25:37 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_gc    *gc_init(void)
{
    t_gc    *gc;

    gc = malloc(sizeof(t_gc));
    if (!gc)
        return (NULL);
    gc->head = NULL;
    return (gc);
}

void    gc_add(t_gc *gc, void *ptr)
{
    t_gc_node   *new_node;

    new_node = malloc(sizeof(t_gc_node));
    if (!new_node)
        return ;
    new_node->ptr = ptr;
    new_node->next = gc->head;
    gc->head = new_node;
}

void    *gc_malloc(t_gc *gc, size_t size)
{
    void    *ptr;

    ptr = malloc(size);
    if (!ptr)
        return ;
    gc_add(gc, ptr);
    return (ptr);
}

void    gc_clear(t_gc *gc)
{
    t_gc_node   *tmp;

    while (gc && gc->head)
    {
        tmp = gc->head->next;
        if (gc->head->ptr)
            free(gc->head->ptr);
        free(gc->head);
        gc->head = tmp;
    }
}

void    gc_free(t_gc *gc, void *ptr)
{
    
}