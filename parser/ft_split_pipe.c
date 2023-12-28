/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:04:28 by tpoungla          #+#    #+#             */
/*   Updated: 2023/12/26 16:10:54 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**get_split(char const *s, char c, char **res)
{
	size_t	i;
	size_t	big_i;

	i = 0;
	big_i = 0;
	while (s[i] && i <= ft_strlen(s))
	{
		if (s[i] != c)
		{
			res[big_i] = ft_substr(s, i, how_long(&s[i], c));
			i = i + how_long(&s[i], c);
			big_i++;
		}
		if (s[i] == c)
			i++;
	}
	res[big_i] = NULL;
	return (res);
}

static size_t	count_on_me(char const *s, char c)
{
	int		word;
	int		skip;
	char	quote_trigger;

	quote_trigger = 0;
	skip = 0;
	word = 0;
	while (*s)
	{
		quote_trigger = get_quote_trigger(quote_trigger, s);
		if (*s == c && skip == 1 && quote_trigger == 0)
			skip = 0;
		if (*s != c && skip == 0)
		{
			word++;
			skip = 1;
		}
		s++;
	}
	if (quote_trigger != 0)
		return (-1);
	return (word);
}

static size_t	how_long(char const *s, char c)
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
		count++;
		s++;
	}
	return (count);
}

char	**ft_split_pipe(char const *s, char c)
{
	char	**resplit;
	size_t	i;
	size_t	big_i;
	int		word;

	if (!s)
		return (0);
	i = 0;
	big_i = 0;
	word = count_on_me(s, c);
	//dprintf(2, "word %d\n", word);
	if (word <= 0 || word == -1)
		return (NULL);
	resplit = ft_calloc((sizeof(char *)), (word + 1));
	if (!resplit)
		return (0);
	resplit = get_split(s, c, resplit);
	return (resplit);
}
