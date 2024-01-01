/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 23:38:36 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/01 17:14:22 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**gget_split(char const *s, char c, char **res)
{
	size_t	i;
	size_t	big_i;

	i = 0;
	big_i = 0;
	while (s[i] && i <= ft_strlen(s))
	{
		if (s[i] != c)
		{
			res[big_i] = ft_substr(s, i, hhow_long(&s[i], c));
			i = i + hhow_long(&s[i], c);
			big_i++;
		}
		if (s[i] == c)
			i++;
	}
	res[big_i] = NULL;
	return (res);
}

int	inside_ccount(char const *s, int skip, char qt, int *word)
{
	char	c;

	c = ' ';
	qt = get_quote_trigger(qt, s);
	if (*s == c && skip == 1 && qt == 0)
		return (0);
	if (*s != c && skip == 0 && !is_redirect(*s))
	{
		*word += 1;
		return (1);
	}
	return (skip);
}

size_t	ccount_on_me(char const *s)
{
	int		word;
	int		skip;
	char	quote_trigger;

	quote_trigger = 0;
	skip = 0;
	word = 0;
	while (*s)
	{
		skip = inside_ccount(s, skip, quote_trigger, &word);
		if (is_redirect(*s))
		{
			if (skip == 1)
				skip = 0;
			word++;
			s = count_for_redirect(s);
		}
		s++;
	}
	if (quote_trigger != 0)
		return (-1);
	return (word);
}

size_t	hhow_long(char const *s, char c)
{
	size_t	count;
	char	quote_trigger;

	quote_trigger = 0;
	count = 0;
	while (*s)
	{
		quote_trigger = get_quote_trigger(quote_trigger, s);
		if (*s == c && quote_trigger == 0)
			return (count);
		if (is_redirect(*s) && quote_trigger == 0)
			return (how_long_redirect(s, count));
		count++;
		s++;
	}
	return (count);
}

char	**ft_split_sp(char const *s, char c)
{
	char	**resplit;
	int		word;

	if (!s)
		return (0);
	word = ccount_on_me(s);
	if (word == -1)
		return (NULL);
	resplit = ft_calloc((sizeof(char *)), (word + 1));
	if (!resplit)
		return (0);
	resplit = gget_split(s, c, resplit);
	return (resplit);
}
