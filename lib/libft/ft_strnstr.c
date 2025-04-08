/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:49:55 by jemorais          #+#    #+#             */
/*   Updated: 2025/02/07 18:28:57 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	little_len = ft_strlen(little);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (j + 1 == little_len)
				return ((char *) big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     const char *big = "Hello, this is a test string.";
//     const char *little = "test";
//     size_t len;

//     // Teste 1: Substring encontrada dentro do limite
//     len = 25;
//     printf("Teste 1: Substring encontrada dentro do limite\n");
//     printf("ft_strnstr: %s\n", ft_strnstr(big, little, len));
//     //printf("strnstr:    %d\n\n", strnstr(big, little, len));

//     // Teste 2: Substring maior que o limite
//     len = 10;
//     printf("Teste 2: Substring maior que o limite\n");
//     printf("ft_strnstr: %s\n", ft_strnstr(big, little, len));
//     //printf("strnstr:    %d\n\n", strnstr(big, little, len));

//     // Teste 3: Substring vazia
//     little = "";
//     len = 30;
//     printf("Teste 3: Substring vazia\n");
//     printf("ft_strnstr: %s\n", ft_strnstr(big, little, len));
//     //printf("strnstr:    %d\n\n", strnstr(big, little, len));

//     // Teste 4: Substring não encontrada
//     little = "nonexistent";
//     len = 30;
//     printf("Teste 4: Substring não encontrada\n");
//     printf("ft_strnstr: %s\n", ft_strnstr(big, little, len));
//     //printf("strnstr:    %d\n\n", strnstr(big, little, len));

//     return 0;
// }
