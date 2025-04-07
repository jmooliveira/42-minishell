/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:40:32 by jemorais          #+#    #+#             */
/*   Updated: 2024/11/12 12:29:34 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (size + src_len);
	while (dst_len + i + 1 < size && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     char dst1[30] = "Hello ";
//     char src1[] = "World!";
//     //char dst2[30] = "Hello ";
//     //char src2[] = "World!";
//     size_t size;

//     // Teste 1: Concatenar com tamanho suficiente
//     size = 30;
//     printf("Teste 1: Concatenar com tamanho suficiente\n");
//     ft_strlcat(dst1, src1, size);
//     //strlcat(dst2, src2, size);
//     printf("ft_strlcat: %s\n", dst1);
//     //printf("strlcat:    %s\n\n", dst2);

//     // Teste 2: Concatenar com tamanho insuficiente (a string de origem será truncada)
//     char dst3[10] = "Hello ";
//     char src3[] = "World!";
//     //char dst4[10] = "Hello ";
//     //char src4[] = "World!";
//     size = 10;
//     printf("Teste 2: Concatenar com tamanho insuficiente (string truncada)\n");
//     ft_strlcat(dst3, src3, size);
//     //strlcat(dst4, src4, size);
//     printf("ft_strlcat: %s\n", dst3);
//     //printf("strlcat:    %s\n\n", dst4);

//     // Teste 3: Concatenar com string de origem vazia
//     char dst5[30] = "Hello ";
//     char src5[] = "";
//     //char dst6[30] = "Hello ";
//     //char src6[] = "";
//     size = 30;
//     printf("Teste 3: Concatenar com string de origem vazia\n");
//     ft_strlcat(dst5, src5, size);
//     //strlcat(dst6, src6, size);
//     printf("ft_strlcat: %s\n", dst5);
//     //printf("strlcat:    %s\n\n", dst6);

//     // Teste 4: Concatenar com destino cheio
//     char dst7[7] = "Hello ";
//     char src7[] = "World!";
//     //char dst8[7] = "Hello ";
//     //char src8[] = "World!";
//     size = 7;
//     printf("Teste 4: Concatenar com destino já cheio\n");
//     ft_strlcat(dst7, src7, size);
//     //strlcat(dst8, src8, size);
//     printf("ft_strlcat: %s\n", dst7);
//     //printf("strlcat:    %s\n\n", dst8);

//     return 0;
// }
