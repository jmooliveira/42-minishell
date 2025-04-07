/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:05:50 by jemorais          #+#    #+#             */
/*   Updated: 2024/10/30 13:47:11 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

// int	main(void)
// {
// 	char	c;

// 	scanf("%c", &c);
// 	printf ("%c\n", ft_toupper(c));
// 	printf ("%c\n", toupper(c));
// 	return (0);
// }
