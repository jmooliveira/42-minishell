/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:49:09 by jemorais          #+#    #+#             */
/*   Updated: 2024/11/12 12:23:09 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	else
	{
		while (src[i] && (i < size - 1))
		{
			dst[i] = src[i];
			i++;
		}
	}
	if (size > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

// #include <stdio.h>
// #include <string.h>
// #include "libft.h"

// int main()
// {
//     char src[] = "Hello, World!";
//     char dst1[20];
//     //char dst2[20];
//     size_t size;

//     // Teste 1: Copiar uma string inteira com tamanho suficiente
//     size = 20;
//     printf("Teste 1: Copiar string inteira (tamanho suficiente)\n");
//     ft_strlcpy(dst1, src, size);
//     //strlcpy(dst2, src, size);
//     printf("ft_strlcpy: %s\n", dst1);
//     //printf("strlcpy:    %s\n\n", dst2);

//     // Teste 2: Copiar string truncada (tamanho pequeno)
//     size = 5;
//     printf("Teste 2: Copiar string truncada (tamanho pequeno)\n");
//     ft_strlcpy(dst1, src, size);
//     //strlcpy(dst2, src, size);
//     printf("ft_strlcpy: %s\n", dst1);
//     //printf("strlcpy:    %s\n\n", dst2);

//     // Teste 3: Copiar para destino com tamanho zero
//     size = 0;
//     printf("Teste 3: Copiar para destino com tamanho zero\n");
//     printf("ft_strlcpy: %zu\n", ft_strlcpy(dst1, src, size)); // Apenas o comprimento da string de origem será retornado
//     //printf("strlcpy:    %zu\n\n", strlcpy(dst2, src, size));

//     return 0;
// }

