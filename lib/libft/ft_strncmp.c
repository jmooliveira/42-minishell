/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:45:29 by jemorais          #+#    #+#             */
/*   Updated: 2025/02/07 18:28:57 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < n - 1)
		i++;
	return (str1[i] - str2[i]);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     const char *str1 = "Hello, world!";
//     const char *str2 = "Hello, world!";
//     const char *str3 = "Hello";
//     const char *str4 = "Hi, world!";

//     size_t n = 1;

//     // Teste 1: Comparação igual
//     printf("Teste 1: Comparação igual (Hello)\n");
//     printf("ft_strncmp: %d\n", ft_strncmp(str1, str2, n));
//     printf("strncmp:    %d\n\n", strncmp(str1, str2, n));

//     // Teste 2: Comparação parcial (Hello vs Hello)
//     printf("Teste 2: Comparação parcial (Hello vs Hello)\n");
//     printf("ft_strncmp: %d\n", ft_strncmp(str1, str3, n));
//     printf("strncmp:    %d\n\n", strncmp(str1, str3, n));

//     // Teste 3: Comparação com strings diferentes
//     printf("Teste 3: Comparação com strings diferentes (Hello vs Hi)\n");
//     printf("ft_strncmp: %d\n", ft_strncmp(str1, str4, n));
//     printf("strncmp:    %d\n\n", strncmp(str1, str4, n));

//     // Teste 4: Comparação com n = 0 (sempre igual)
//     printf("Teste 4: Comparação com n = 0\n");
//     printf("ft_strncmp: %d\n", ft_strncmp(str1, str2, 0));
//     printf("strncmp:    %d\n\n", strncmp(str1, str2, 0));

//     return 0;
// }
