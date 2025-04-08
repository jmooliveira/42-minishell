/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:42:23 by jemorais          #+#    #+#             */
/*   Updated: 2025/02/07 18:30:30 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_check_ptr(void *ptr)
{
	if (ptr == 0)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	else
		return (ft_putnbr_baseptr((unsigned long)ptr, 1));
}

int	ft_putnbr_baseptr(unsigned long nb, int flag)
{
	int	count;

	count = 0;
	if (flag == 1)
	{
		write(1, "0x", 2);
		flag = 0;
		count += 2;
	}
	if (nb > 15)
		count += ft_putnbr_baseptr(nb / 16, flag);
	nb = nb % 16;
	if (nb > 9)
		count += ft_putchar(nb - 10 + 'a');
	else
		count += ft_putchar(nb + '0');
	return (count);
}

int	ft_putstr(char *s)
{
	int		i;
	char	*str;

	str = s;
	if (str == NULL)
	{
		write (1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putchar(char c)
{
	int	count;

	count = 1;
	write(1, &c, 1);
	return (count);
}
