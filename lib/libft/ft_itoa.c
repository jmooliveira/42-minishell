/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:01:02 by jemorais          #+#    #+#             */
/*   Updated: 2025/02/07 18:28:57 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_nbr_digit(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (++i);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_at(char *nbr, int digits, unsigned int nb)
{
	while (digits > 0)
	{
		nbr[digits - 1] = nb % 10 + '0';
		nb /= 10;
		digits--;
	}
}

char	*ft_itoa(int n)
{
	char			*nbr;
	unsigned int	nbr_digits;
	unsigned int	nbr_number;

	nbr_digits = ft_nbr_digit(n);
	if (n < 0)
	{
		nbr_digits++;
		nbr = (char *)ft_calloc(nbr_digits + 1, sizeof(char));
		if (!nbr)
			return (NULL);
		nbr_number = -n;
		ft_at(nbr, nbr_digits, nbr_number);
		nbr[0] = '-';
	}
	else
	{
		nbr = (char *)ft_calloc(nbr_digits + 1, sizeof(char));
		if (!nbr)
			return (NULL);
		ft_at(nbr, nbr_digits, n);
	}
	return (nbr);
}

// int	main(void)
// {
// 	int	nb = 0;

// 	printf("%s\n", ft_itoa(nb));
// 	return (0);
// }
