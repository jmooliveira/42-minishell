/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:23:18 by jemorais          #+#    #+#             */
/*   Updated: 2024/11/12 12:56:59 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;
	size_t			i;

	if (n == 0)
		return (dest);
	if (dest == NULL && src == NULL)
		return (NULL);
	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (dest);
}

#include <stdio.h>
#include <string.h>

// int main() {
//     // Teste 1: Copiar uma sequência de bytes de um array para outro
//     char src1[] = "Hello, World!";
//     char dest1[20];
//     ft_memcpy(dest1, src1, 13);  // Copiar 13 bytes de src1 para dest1
//     printf("Teste 1 (ft_memcpy): %s\n", dest1);  // Esperado: "Hello, World!"

//     // Teste 2: Copiar 0 bytes (não deve ocorrer cópia)
//     char src2[] = "Hello, World!";
//     char dest2[20];
//     ft_memcpy(dest2, src2, 0);  // Não deve copiar nada
//     printf("Teste 2 (ft_memcpy): %s\n", dest2);  // Esperado: Dest2 não modificado (sem conteúdo)

//     // Teste 3: Copiar de um buffer para outro de tamanho suficiente
//     char src3[] = "12345";
//     char dest3[10];
//     ft_memcpy(dest3, src3, 5);  // Copiar os primeiros 5 bytes de src3
//     printf("Teste 3 (ft_memcpy): %s\n", dest3);  // Esperado: "12345"

//     // // Teste 4: Teste com ponteiros NULL
//     // char *src4 = NULL;
//     // char dest4[10];
//     // char *result4 = ft_memcpy(dest4, src4, 5);
// 	// Não deve funcionar (src4 é NULL)
//     // printf("Teste 4 (ft_memcpy): %p\n", result4);  // Esperado: NULL

//     // Teste 5: Teste de sobreposição de memória (copiar para o próprio array)
//     char src5[] = "Test overlap";
//     ft_memcpy(src5, src5 + 5, 5);  // Copiar parte de src5 para a própria src5 (sobreposição)
//     printf("Teste 5 (ft_memcpy): %s\n", src5);  // Esperado: "overlap overlap"

//     // Teste 6: Teste de comparação com a função nativa memcpy
//     char src6[] = "Comparison Test";
//     char dest6_ft[20], dest6_std[20];
//     ft_memcpy(dest6_ft, src6, 15);  // Usando ft_memcpy
//     memcpy(dest6_std, src6, 15);    // Usando memcpy padrão
//     printf("Teste 6 (ft_memcpy vs memcpy):\n");
//     printf("ft_memcpy: %s\n", dest6_ft);  // Esperado: "Comparison Test"
//     printf("memcpy: %s\n", dest6_std);    // Esperado: "Comparison Test"

//     return 0;
// }
