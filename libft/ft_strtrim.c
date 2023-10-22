/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 12:42:36 by pruenrua          #+#    #+#             */
/*   Updated: 2022/08/31 20:38:03 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lemme_see(char const *ss, char const *sed)
{
	while (*sed)
	{
		if (*ss == *sed)
			return (1);
		sed++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*trimmed;

	if (!s1 || !set)
		return (0);
	start = 0;
	while (s1[start] && lemme_see(&s1[start], set))
		start++;
	end = ft_strlen(s1);
	if (end > 0)
		end = end - 1;
	while (end > start && s1[end] && lemme_see(&s1[end], set))
		end--;
	trimmed = malloc(((end + 1) - start) + 1);
	if (!trimmed)
		return (0);
	i = 0;
	while (start <= end)
	{
		trimmed[i++] = s1[start++];
	}
	trimmed[i] = '\0';
	return (trimmed);
}
/*
int main()
{
	char *s = "oooohellowooo";
	char *set = "o";
	char *result = ft_strtrim(s,set);

	printf("%s", result);
}*/
