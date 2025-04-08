/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:58:34 by jemorais          #+#    #+#             */
/*   Updated: 2025/02/07 18:28:57 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// #include <stdio.h>
// #include <string.h>

// // int that case NULL, should be segmentatio fault

// int main(void) {
//     const char *test_cases[] = {
//         "Hello, world!",
//         "",
//         "42 São Paulo",
//         "Testing123",
//         NULL
//     };

//     int i = 0;
//     while (i < 5) {
//         const char *str = test_cases[i];

//         // if (str == NULL) {
//         //     printf("Test case %d: NULL input\n", i);
//         //     printf("ft_strlen result: (undefined)\n");
//         //     printf("strlen result: (undefined)\n\n");
//         // } else {
//             printf("Test case %d: \"%s\"\n", i, str);
//             printf("ft_strlen result: %zu\n", ft_strlen(str));
//             printf("strlen result: %zu\n\n", strlen(str));
//         // }
//         i++;
//     }

//     return 0;
// }
