/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:40:17 by jemorais          #+#    #+#             */
/*   Updated: 2025/02/07 18:28:57 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*temp;
	size_t			total_size;
	size_t			i;

	total_size = nmemb * size;
	if (nmemb != 0 && (total_size / nmemb != size))
		return (NULL);
	i = 0;
	temp = malloc (nmemb * size);
	if (!temp)
		return (NULL);
	while (i < size * nmemb)
		temp[i++] = 0;
	return (temp);
}

// int	main(void)
// {
// 	char	*nmem;
// 	size_t	nb;

// 	nmem = 'a';
// 	nb = -1;
// 	ft_calloc(nmem, nb);
// 	return (0);
// }
