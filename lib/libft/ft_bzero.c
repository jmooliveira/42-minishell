/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:17:36 by jemorais          #+#    #+#             */
/*   Updated: 2025/02/07 18:28:57 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	zero;

	i = 0;
	ptr = s;
	zero = 0;
	while (i < n)
	{
		*ptr = zero;
		ptr++;
		i++;
	}
}

// int	main(void)
// {
// 	char	c[9] = "Jefferson";
// 	char	d[8] = "Oliveira";
// 	size_t	i = 5;

// 	ft_bzero(c, i);
// 	printf("%s\n", &c[5]);
// 	bzero(d, i);
// 	printf("%s\n", d);
// 	return (0);
// }
