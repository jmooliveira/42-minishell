/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:26:42 by jemorais          #+#    #+#             */
/*   Updated: 2024/11/12 12:08:32 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	flag;

	i = 0;
	flag = -1;
	while (s[i])
	{
		if (s[i] == (char) c)
			flag = i;
		i++;
	}
	if ((unsigned char) c == '\0')
		return ((char *)s + i);
	if (flag != -1)
		return ((char *)s + flag);
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>

// int main()
// {
//     const char *str = "Hello, world!";
//     int char_to_find = 'o';        // Caractere comum presente mais de uma vez
//     int char_unique = 'H';         // Caractere presente apenas uma vez
//     int char_not_in_str = 'x';     // Caractere ausente
//     int char_to_find_last = '\0';  // Caractere nulo

//     // Teste 1: Caractere comum presente mais de uma vez
//     printf("Teste 1: Última ocorrência de 'o'\n");
//     printf("ft_strrchr: %s\n", ft_strrchr(str, char_to_find));
//     printf("strrchr:    %s\n\n", strrchr(str, char_to_find));

//     // Teste 2: Caractere presente apenas uma vez
//     printf("Teste 2: Única ocorrência de 'H'\n");
//     printf("ft_strrchr: %s\n", ft_strrchr(str, char_unique));
//     printf("strrchr:    %s\n\n", strrchr(str, char_unique));

//     // Teste 3: Caractere ausente
//     printf("Teste 3: Caractere ausente 'x'\n");
//     printf("ft_strrchr: %p\n", ft_strrchr(str, char_not_in_str));
//     printf("strrchr:    %p\n\n", strrchr(str, char_not_in_str));

//     // Teste 4: Caractere nulo ('\0')
//     printf("Teste 4: Caractere nulo '\\0'\n");
//     printf("ft_strrchr: %s\n", ft_strrchr(str, char_to_find_last));
//     printf("strrchr:    %s\n\n", strrchr(str, char_to_find_last));

//     // Teste 5: String vazia
//     const char *empty_str = "";
//     printf("Teste 5: String vazia com '\\0'\n");
//     printf("ft_strrchr: %p\n", ft_strrchr(empty_str, '\0'));
//     printf("strrchr:    %p\n\n", strrchr(empty_str, '\0'));

//     return 0;
// }

