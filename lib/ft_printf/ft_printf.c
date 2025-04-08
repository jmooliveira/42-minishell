/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:04:18 by jemorais          #+#    #+#             */
/*   Updated: 2025/02/07 18:30:30 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_check_arg(va_list print, const char *frt)
{
	int	count;

	count = 0;
	if (*frt == 'c')
		count += ft_putchar(va_arg(print, int));
	else if (*frt == 's')
		count += ft_putstr(va_arg(print, char *));
	else if (*frt == 'p')
		count += ft_check_ptr(va_arg(print, void *));
	else if (*frt == 'd' || *frt == 'i')
		count += ft_putnbr(va_arg(print, int));
	else if (*frt == 'u')
		count += ft_putnbr_unsigned(va_arg(print, long int));
	else if (*frt == 'x' || *frt == 'X')
		count += ft_putnbr_base(va_arg(print, int), frt);
	else if (*frt == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_find_parameter(va_list print, const char *frt)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (frt[i])
	{
		if (frt[i] == '%')
		{
			i++;
			count += ft_check_arg(print, &frt[i]);
		}
		else
		{
			write (1, &frt[i], 1);
			count++;
		}
		i++;
	}
	return (count);
}

int	ft_printf(const char *frt, ...)
{
	va_list	print;
	int		count;

	if (!frt)
		return (-1);
	count = 0;
	va_start(print, frt);
	count = ft_find_parameter(print, frt);
	va_end(print);
	return (count);
}

/*********************************************/
// #include <stdio.h>
// #include <limits.h>

// void printcmp(int a, int b)
// {
//     if (a == b)
//     {
//         ft_printf("OK\n");
//     }
//     else
//         ft_printf("KO --!\n");
// }

// int	main(void)
// {
// 	char ch = 'A';
// 	char *s = "string";
// 	int i = -42;
// 	int j = -42;
// 	unsigned int u = 42;
//     int count;

//     count = 0;

// //cc -Wall -Wextra -Werror
// //ft_printf.h ft_printf_utils1.c ft_printf_utils2.c
// //compile with -w

// 	//Test 1: c, s, d, i
// 	printf("Test1\n");
// 	count = ft_printf("%s  %c  %d  %i\n", s, ch, i, i);
// 	printf("ft_printf count = %d\n\n", count);
// 	count = printf("%s  %c  %d  %i\n", s, ch, i, i);
//     printf("printf count = %d\n\n\n", count);

// 	//Test 2: p
// 	printf("Test2\n");
//     count = ft_printf("p: %p\n", s);
// 	printf("ft_printf count = %d\n\n", count);
// 	count = printf("p: %p\n", s);
// 	printf("printf count = %d\n\n\n", count);

// 	//Test 3: u
// 	printf("Test3\n");
//     count = ft_printf("unsigned: %u\n", u);
// 	printf("ft_printf count = %d\n\n", count);
// 	count = printf("unsigned: %u\n", u);
// 	printf("printf count = %d\n\n\n", count);

// 	//Test 4: u but sending negative int
// 	printf("Test4\n");
//     count = ft_printf("unsigned: %u\n", j);
// 	printf("ft_printf count = %d\n\n", count);
// 	count = printf("unsigned: %u\n", j);
// 	printf("printf count = %d\n\n\n", count);

// 	//Test 5: x
// 	printf("Test5\n");
// 	count = ft_printf("hex: %x\n", i);
// 	printf("ft_printf count = %d\n\n", count);
// 	ft_printf("hex: %x\n", i);
// 	printf("printf count = %d\n\n\n", count);

// 	//Test 6: X
// 	printf("Test6\n");
// 	count = ft_printf("hex: %X\n", i);
// 	printf("ft_printf count = %d\n\n", count);
// 	ft_printf("hex: %X\n", i);
// 	printf("printf count = %d\n\n\n", count);

// 	//Test 7: %%
// 	printf("Test7\n");
// 	count = ft_printf("percentage %%\n");
// 	printf("ft_printf count = %d\n\n", count);
// 	count = printf("percentage %%\n");
// 	printf("printf count = %d\n\n\n", count);

// 	//Test 8: %j - an invalid argument
// 	printf("Test8\n");
//     count = ft_printf("f%jk\n", i);
// 	printf("ft_printf count = %d\n\n", count);
// 	count = printf("f%jk\n", i);
// 	printf("printf count = %d\n\n\n", count);

// 	//Test 9: s (null)
// 	printf("Test9\n");
// 	count = ft_printf(" NULL %s NULL\n", NULL);
// 	printf("ft_printf count = %d\n\n", count);
// 	count = printf(" NULL %s NULL\n", NULL);
// 	printf("printf count = %d\n\n\n", count);

// 	//Test 10: s (sending 0)
// 	printf("Test10\n");
// 	count = ft_printf(" NULL %s NULL\n", 0);
// 	printf("ft_printf count = %d\n\n", count);
// 	count = printf(" NULL %s NULL\n", 0);
// 	printf("printf count = %d\n\n\n", count);

// 	//Test 11: p (long address)
// 	//(long) LONG_MAX: 2147483647  LONG_MIN: -2147483648
// 	printf("Test11\n");
// 	count = ft_printf(" %p %p \n", LONG_MIN, LONG_MAX);
// 	printf("ft_printf count = %d\n\n", count);
// 	count = printf(" %p %p \n", LONG_MIN, LONG_MAX);
// 	printf("printf count = %d\n\n\n", count);

// 	//Test 12: p (unsigned long address)
// 	printf("Test12\n");
// 	count = ft_printf(" %p %p \n", ULONG_MAX, -ULONG_MAX);
// 	printf("ft_printf count = %d\n\n", count);
// 	count = printf(" %p %p \n", ULONG_MAX, -ULONG_MAX);
// 	printf("printf count = %d\n\n\n", count);

// 	//Test 13: p (nil) (sending 0)
// 	printf("Test13\n");
// 	count = ft_printf(" %p %p \n", 0, 0);
// 	printf("ft_printf count = %d\n\n", count);
// 	count = printf(" %p %p \n", 0, 0);
// 	printf("printf count = %d\n\n\n", count);

// 	//Test 14: hex (sending 0)
// 	printf("Test14\n");
// 	count = ft_printf(" %x %x \n", 0, 0);
// 	printf("ft_printf count = %d\n\n", count);
// 	count = printf(" %x %x \n", 0, 0);
// 	printf("printf count = %d\n\n\n", count);

// 	//Test 15: with no arguments
// 	printf("Test15\n");
// 	count = ft_printf("hi %d hello\n");
// 	printf("ft_printf count = %d\n\n", count);
// 	count = printf("hi %d hello\n");
// 	printf("printf count = %d\n\n\n", count);

// 	//Test 16
// 	//undefined behavior, it can lead to seg fault or crash
// 	printf("Test16\n");
// 	count = printf(NULL);
// 	printf("printf count = %d\n\n", count);
// 	count = ft_printf(NULL);
// 	printf("ft_printf count = %d\n\n\n", count);

// 	//Test 17
// 	printf("Test17\n");
// 	count = printf("%s\n", "");
// 	printf("printf count = %d\n", count);
// 	count = ft_printf("%s\n", "");
// 	printf("ft_printf count = %d\n\n", count);

//     char    *str = "It's raining";
//     char    *nulo = NULL;
//     char    **ptr;
//     int     myfunc;
//     int     original;
//     ptr = &str;

//     ft_printf("---------my func-----------\n");
//     myfunc = ft_printf("c flag: %c|%c|%c|%c|%c\n", 'r', str[2],
//      97 - 32, *str, 48);

//     ft_printf("\n---------original-----------\n");
// 	original = printf("c flag: %c|%c|%c|%c|%c\n", 'r', str[2],
//      97 - 32, *str, 48);

//     ft_printf("\n---------result-----------\n");
//     printcmp(myfunc, original);

//     ft_printf("\n---------my func-----------\n");
//     myfunc = ft_printf("s flag: %s|%s|%s|%s|%s|%s\n", "It's raining",
//      str, str + 2, "", "-", nulo);

//     ft_printf("\n---------original-----------\n");
//     original = printf("s flag: %s|%s|%s|%s|%s|%s\n", "It's raining",
//      str, str + 2, "", "-", nulo);

//     ft_printf("\n---------result-----------\n");
//     printcmp(myfunc, original);

//     ft_printf("\n---------my func-----------\n");
//     myfunc = ft_printf("p flag: %p|%p|%p|%p|%p|%p\n", str, &str, ptr, &ptr,
// 	nulo, &nulo);

//     ft_printf("\n---------original-----------\n");
//     original = printf("p flag: %p|%p|%p|%p|%p|%p\n", str, &str, ptr, &ptr,
// 	nulo, &nulo);

//     ft_printf("\n---------result-----------\n");
//     printcmp(myfunc, original);

//     ft_printf("\n---------my func-----------\n");
//     myfunc = ft_printf("d flag: %d|%d|%d|%d|%d\n", 7, -7, 0,
//      2147483647, -2147483648);

//     ft_printf("\n---------original-----------\n");
//     original = printf("d flag: %d|%d|%d|%d|%d\n", 7, -7, 0,
//      2147483647, -2147483647 - 1);

//     ft_printf("\n---------result-----------\n");
//     printcmp(myfunc, original);

//     ft_printf("\n---------my func-----------\n");
//     myfunc = ft_printf("i flag: %i|%i|%i|%i|%i\n", 7, -7, 0,
//      2147483647, -2147483648);

//     ft_printf("\n---------original-----------\n");
//     original = printf("i flag: %i|%i|%i|%i|%i\n", 7, -7, 0,
//      2147483647, -2147483647 - 1);

//     ft_printf("\n---------result-----------\n");
//     printcmp(myfunc, original);

//     ft_printf("\n---------my func-----------\n");
//     myfunc = ft_printf("u flag: %u|%u|%u|%u|%u\n", 7, -7, 0,
//      2147483647, -2147483648);

//     ft_printf("\n---------original-----------\n");
//     original = printf("u flag: %u|%u|%u|%u|%u\n", 7, -7, 0,
//      2147483647, -2147483647 - 1);

//     ft_printf("\n---------result-----------\n");
//     printcmp(myfunc, original);

//     ft_printf("\n---------my func-----------\n");
//     myfunc = ft_printf("x flag: %x|%x|%x|%x|%x\n", 7, -7, 0,
//      2147483647, -2147483648);

//     ft_printf("\n---------original-----------\n");
//     original = printf("x flag: %x|%x|%x|%x|%x\n", 7, -7, 0,
//      2147483647, -2147483647 - 1);

//     ft_printf("\n---------result-----------\n");
//     printcmp(myfunc, original);

//     ft_printf("\n---------my func-----------\n");
//     myfunc = ft_printf("X flag: %X|%X|%X|%X|%X\n", 7, -7, 0,
//      2147483647, -2147483648);

//     ft_printf("\n---------original-----------\n");
//     original = printf("X flag: %X|%X|%X|%X|%X\n", 7, -7, 0,
//      2147483647, -2147483647 - 1);

//     ft_printf("\n---------result-----------\n");
//     printcmp(myfunc, original);

//     ft_printf("\n---------my func-----------\n");
//     myfunc = ft_printf("%% flag: %% | %%|%% \n");

//     ft_printf("\n---------original-----------\n");
//     original = printf("%% flag: %% | %%|%% \n");

//     ft_printf("\n---------result-----------\n");
//     printcmp(myfunc, original);

//     ft_printf("\n---------my func-----------\n");
//     myfunc = ft_printf(", I've printed %d characters!\n",
//      ft_printf("d flag: %d|%d|%d|%d", 0, -37, 37, 187398217));

//     ft_printf("\n---------original-----------\n");
//     original = printf(", I've printed %d characters!\n",
//      printf("d flag: %d|%d|%d|%d", 0, -37, 37, 187398217));

//     ft_printf("\n---------result-----------\n");
//     printcmp(myfunc, original);

//     ft_printf("\n---------my func-----------\n");
//     myfunc = ft_printf(", I've printed %d characters!\n",
//      ft_printf("d flag: %d|%d|%d|%d", 0, -22222, 'n', 0));

//     ft_printf("\n---------original-----------\n");
//     original = printf(", I've printed %d characters!\n",
//      printf("d flag: %d|%d|%d|%d", 0, -22222, 'n', 0));

//     ft_printf("\n---------result-----------\n");
//     printcmp(myfunc, original);

//     ft_printf("\n---------my func-----------\n");
//     myfunc = ft_printf(", I've printed %d characters!\n",
//      ft_printf("INT MIN: %d", -2147483647 - 1));

//     ft_printf("\n---------original-----------\n");
//     original = printf(", I've printed %d characters!\n",
//      printf("INT MIN: %d", -2147483647 - 1));

//     ft_printf("\n---------result-----------\n");
//     printcmp(myfunc, original);

//     ft_printf("\n---------my func-----------\n");
//     myfunc = ft_printf("MIXED:%c|%s|%p|%d|%i|%u|%x|%X|%%\n", str[6],
// 	nulo, str, -912387, 00000, -99, 743, 743);

//     ft_printf("\n---------original-----------\n");
//     original = printf("MIXED:%c|%s|%p|%d|%i|%u|%x|%X|%%\n", str[6],
// 	nulo, str, -912387, 00000, -99, 743, 743);

//     ft_printf("\n---------result-----------\n");
//     printcmp(myfunc, original);

//     ft_printf("\n---------my func-----------\n");
//     myfunc = ft_printf(NULL);

//     ft_printf("\n---------original-----------\n");
//     original = printf(NULL);

//     ft_printf("\n---------result-----------\n");
//     printcmp(myfunc, original);
// }

// // int	main(void)
// // {
// // 	char	*name = "Jefferson";
// // 	int		age = 38;

// // 	ft_printf("Meu nome eh % e tenho % anos\n");
// // 	//printf("Meu nome eh % e tenho % anos\n");
// // 	ft_printf("Meu nome eh % s e tenho % d anos. \n", name, age);
// // 	//printf("Meu nome eh % s e tenho % d anos. \n", name, age);
// // 	ft_printf("Meu nome eh % s e tenho %d anos. \n", name, age);
// // 	//printf("Meu nome eh % s e tenho %d anos. \n", name, age);
// // 	//ft_printf("Meu nome eh % d e tenho %s anos. \n", age, name);
// // 	printf("Meu nome eh % d e tenho %s anos. \n", age, name);
// // 	return (0);
// // }
