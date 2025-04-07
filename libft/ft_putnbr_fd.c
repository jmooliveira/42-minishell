/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:02:31 by jemorais          #+#    #+#             */
/*   Updated: 2024/11/13 16:08:53 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			c;
	unsigned int	nb;

	if (n < 0)
	{
		write(fd, "-", 1);
		nb = -1 * (unsigned int)(n);
	}
	else
		nb = (unsigned int) n;
	if (nb > 9)
		ft_putnbr_fd(nb / 10, fd);
	c = 48 + nb % 10;
	write(fd, &c, 1);
}

#include <stdio.h>

int	main(void)
{
	int nb;// = 2147483648;

	scanf("%d", &nb);
	ft_putnbr_fd(nb, 1);
}
