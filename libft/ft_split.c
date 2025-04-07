/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemorais <jemorais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:00:38 by jemorais          #+#    #+#             */
/*   Updated: 2024/11/08 18:27:21 by jemorais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words_count(char const *s, char c)
{
	int	count_words;
	int	i;
	int	flag;

	if (!*s)
		return (0);
	flag = 1;
	i = 0;
	count_words = 0;
	while (s[i])
	{
		if (s[i] != c && s[i] && flag == 1)
		{
			flag = 0;
			count_words++;
		}
		if (s[i] == c)
		{
			flag = 1;
		}
		i++;
	}
	return (count_words);
}

static int	ft_letters_count(char const *s, char c)
{
	int	count_letters;
	int	i;

	i = 0;
	if (!*s)
		return (0);
	count_letters = 0;
	while (s[i] && s[i] != c)
	{
		count_letters++;
		i++;
	}
	return (count_letters);
}

static char	*ft_fill_split(char const *s, char c, int i)
{
	char	*split_str;
	int		j;

	split_str = (char *)ft_calloc(ft_letters_count(&s[i], c) + 1, sizeof(char));
	if (!split_str)
		return (NULL);
	j = 0;
	while (s[i] != c && s[i])
	{
		split_str[j] = s[i];
		i++;
		j++;
	}
	return (split_str);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;

	split = (char **)ft_calloc(ft_words_count(s, c) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < ft_words_count(s, c))
	{
		while (s[i] == c)
			i++;
		split[j] = ft_fill_split(s, c, i);
		if (!split[j])
			return (NULL);
		while (s[i] != c && s[i])
			i++;
		if (split[j][0] != '\0')
			j++;
	}
	return (split);
}

// int	main(void)
// {
// 	char	phr[] = "   lorem   ipsum dolor     sit amet, consectetur
// adipiscing elit. Sed non risus. Suspendisse   "; // recolocar
// 	char	ch = ' ';
// 	char	**ptr;
// 	int		i;

// 	i = 0;
// 	ptr = ft_split(phr, ch);
// 	while(ptr[i] != NULL)
// 	{
// 		printf("%s\n", ptr[i]);
// 		i++;
// 	}
// 	return (0);
// }
