/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils_itoa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarol9 <ancarol9@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:56:44 by ancarol9          #+#    #+#             */
/*   Updated: 2025/07/18 01:56:45 by ancarol9         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static unsigned int	ft_nbr_digit(int n)
{
	unsigned int	count;
	unsigned int	nb;

	count = 1;
	if (n < 0)
		nb = (unsigned int)(-(long)n);
	else
		nb = (unsigned int)n;
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
