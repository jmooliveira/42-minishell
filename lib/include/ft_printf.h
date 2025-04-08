/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:08:27 by jemorais          #+#    #+#             */
/*   Updated: 2024/11/22 11:25:20 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_find_parameter(va_list print, const char *frt);
int	ft_check_arg(va_list print, const char *frt);
int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr_baseptr(unsigned long nb, int flag);
int	ft_check_ptr(void *ptr);
int	ft_putnbr(int n);
int	ft_putnbr_unsigned(unsigned int n);
int	ft_putnbr_base(unsigned int nb, const char *up_lo);

#endif
