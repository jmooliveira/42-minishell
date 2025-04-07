/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:48:49 by jemorais          #+#    #+#             */
/*   Updated: 2024/11/12 13:06:29 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;
	size_t			i;

	if (n == 0)
		return (dest);
	if (dest == NULL && src == NULL)
		return (NULL);
	ptr_dest = (unsigned char *) dest;
	ptr_src = (unsigned char *) src;
	i = 0;
	if (ptr_dest >= ptr_src && ptr_dest < ptr_src + n)
		while (n--)
			ptr_dest[n] = ptr_src[n];
	else
	{
		while (i < n)
		{
			ptr_dest[i] = ptr_src[i];
			i++;
		}
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int main() {
//     // Teste 1: Movendo uma sequência de bytes de um array para outro
//     char src1[] = "Hello, World!";
//     char dest1[20];
//     ft_memmove(dest1, src1, 13);  // Mover 13 bytes de src1 para dest1
//     printf("Teste 1 (ft_memmove): %s\n", dest1);  // Esperado: "Hello, World!"

//     // Teste 2: Movendo 0 bytes (não deve ocorrer movimento)
//     char src2[] = "Hello, World!";
//     char dest2[20];
//     ft_memmove(dest2, src2, 0);  // Não deve mover nada
//     printf("Teste 2 (ft_memmove): %s\n", dest2);  // Esperado: Dest2 não modificado (sem conteúdo)

//     // Teste 3: Movendo de um buffer para outro de tamanho suficiente
//     char src3[] = "12345";
//     char dest3[10];
//     ft_memmove(dest3, src3, 5);  // Mover os primeiros 5 bytes de src3
//     printf("Teste 3 (ft_memmove): %s\n", dest3);  // Esperado: "12345"

//     // Teste 4: Teste com ponteiros NULL
//     //char *src4 = NULL;
//     //char dest4[10];
//     //char *result4 = ft_memmove(dest4, src4, 5);  // Não deve funcionar (src4 é NULL)
//     //printf("Teste 4 (ft_memmove): %p\n", result4);  // Esperado: NULL

//     // Teste 5: Teste de sobreposição de memória (movendo para o próprio array)
//     char src5[] = "Test overlap";
//     ft_memmove(src5 + 5, src5, 5);  // Mover parte de src5 para a própria src5 (sobreposição)
//     printf("Teste 5 (ft_memmove): %s\n", src5);  // Esperado: "overlap overlap"

//     // Teste 6: Teste de comparação com a função nativa memmove
//     char src6[] = "Comparison Test";
//     char dest6_ft[20], dest6_std[20];
//     ft_memmove(dest6_ft, src6, 15);  // Usando ft_memmove
//     memmove(dest6_std, src6, 15);    // Usando memmove padrão
//     printf("Teste 6 (ft_memmove vs memmove):\n");
//     printf("ft_memmove: %s\n", dest6_ft);  // Esperado: "Comparison Test"
//     printf("memmove: %s\n", dest6_std);    // Esperado: "Comparison Test"

//     return 0;
// }

