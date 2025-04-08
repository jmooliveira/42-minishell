/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:50:11 by jemorais          #+#    #+#             */
/*   Updated: 2025/02/07 18:28:57 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return ((char *)s + i);
		i++;
	}
	if ((unsigned char) c == '\0')
		return ((char *)s + i);
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     const char *str = "Hello, world!";
//     int char_to_find = 'o';       // Caractere comum
//     int char_to_find_last = '\0'; // Caractere nulo
//     int char_not_in_str = 'x';    // Caractere ausente

//     // Teste 1: Caractere comum
//     printf("Teste 1: Caractere comum 'o'\n");
//     printf("ft_strchr: %s\n", ft_strchr(str, char_to_find));
//     printf("strchr:    %s\n\n", strchr(str, char_to_find));

//     // Teste 2: Caractere nulo ('\0')
//     printf("Teste 2: Caractere nulo '\\0'\n");
//     printf("ft_strchr: %s\n", ft_strchr(str, char_to_find_last));
//     printf("strchr:    %s\n\n", strchr(str, char_to_find_last));

//     // Teste 3: Caractere ausente
//     printf("Teste 3: Caractere ausente 'x'\n");
//     printf("ft_strchr: %p\n", ft_strchr(str, char_not_in_str));
//     printf("strchr:    %p\n\n", strchr(str, char_not_in_str));

//     // Teste 4: String vazia com caractere nulo
//     const char *empty_str = "";
//     printf("Teste 4: String vazia com '\\0'\n");
//     printf("ft_strchr: %p\n", ft_strchr(empty_str, '\0'));
//     printf("strchr:    %p\n\n", strchr(empty_str, '\0'));

//     return 0;
// }
