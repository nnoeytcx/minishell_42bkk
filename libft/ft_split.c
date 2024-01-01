/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:54:09 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/01 17:12:40 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_on_me(char const *s, char c)
{
	int	word;
	int	skip;

	skip = 0;
	word = 0;
	while (*s)
	{
		if (*s == c && skip == 1)
			skip = 0;
		if (*s != c && skip == 0)
		{
			word++;
			skip = 1;
		}
		s++;
	}
	return (word);
}

static size_t	how_long(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			return (count);
		count++;
		s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**resplit;
	size_t	i;
	size_t	big_i;

	if (!s)
		return (0);
	i = 0;
	big_i = 0;
	resplit = (char **)malloc((sizeof(char *)) * (count_on_me(s, c) + 1));
	if (!resplit)
		return (0);
	while (s[i] && i <= ft_strlen(s))
	{
		if (s[i] != c)
		{
			resplit[big_i] = ft_substr(s, i, how_long(&s[i], c));
			i = i + how_long(&s[i], c);
			big_i++;
		}
		if (s[i] == c)
			i++;
	}
	resplit[big_i] = NULL;
	return (resplit);
}
