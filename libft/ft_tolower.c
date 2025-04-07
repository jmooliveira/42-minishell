/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:27:18 by jemorais          #+#    #+#             */
/*   Updated: 2024/10/30 13:44:16 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

// int	main(void)
// {
// 	char	c;

// 	scanf("%c", &c);
// 	printf ("%c\n", ft_tolower(c));
// 	printf ("%c\n", tolower(c));
// 	return (0);
// }
