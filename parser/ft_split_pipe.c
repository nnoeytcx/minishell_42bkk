/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:04:28 by tpoungla          #+#    #+#             */
/*   Updated: 2023/12/25 00:09:39 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
	if (word == -1)
		return (NULL);
	resplit = ft_calloc((sizeof(char *)), (word + 1));
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
