/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:16:19 by jemorais          #+#    #+#             */
/*   Updated: 2024/10/30 15:45:59 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len_s;
	char			*ptr_s;
	unsigned int	i;

	len_s = ft_strlen(s);
	ptr_s = (char *) ft_calloc (len_s + 1, sizeof(char));
	if (!ptr_s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr_s[i] = f(i, s[i]);
		i++;
	}
	ptr_s[len_s] = '\0';
	return (ptr_s);
}

// char ft_toupper_adapted(unsigned int a, char c)
// {
// 	(void) a;
// 	if (c >= 'a' && c <= 'z')
// 		c -= 32;
// 	return (c);
// }

// int	main(void)
// {
// 	char	src[] = "jefferson";

// 	printf("%s\n", ft_strmapi(src, ft_toupper_adapted));
// 	return (0);
// }
