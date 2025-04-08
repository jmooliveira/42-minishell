/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:48:17 by jemorais          #+#    #+#             */
/*   Updated: 2025/02/07 18:30:30 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_putnbr_base(unsigned int nb, const char *up_lo)
{
	int	count;

	count = 0;
	if (nb > 15)
	{
		count += ft_putnbr_base(nb / 16, up_lo);
		nb = nb % 16;
	}
	if (*up_lo == 'X')
	{
		if (nb > 9)
			count += ft_putchar(nb - 10 + 'A');
		else
			count += ft_putchar(nb + '0');
	}
	else
	{
		if (nb > 9)
			count += ft_putchar(nb - 10 + 'a');
		else
			count += ft_putchar(nb + '0');
	}
	return (count);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	char			c;
	unsigned int	nb;
	int				count;

	nb = n;
	count = 0;
	if (nb > 9)
		count += ft_putnbr(nb / 10);
	c = 48 + nb % 10;
	write(1, &c, 1);
	count++;
	return (count);
}

int	ft_putnbr(int n)
{
	char			c;
	unsigned int	nb;
	int				count;

	count = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		nb = -1 * (unsigned int)(n);
		count++;
	}
	else
		nb = (unsigned int) n;
	if (nb > 9)
		count += ft_putnbr(nb / 10);
	c = '0' + nb % 10;
	write(1, &c, 1);
	count++;
	return (count);
}
