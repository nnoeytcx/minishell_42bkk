/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sp_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 23:55:04 by tpoungla          #+#    #+#             */
/*   Updated: 2023/12/24 23:55:32 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_redirect(char c)
{
	if (c == '>' || c == '<')
		return (1);
	else
		return (0);
}

size_t	how_long_redirect(char const *s, size_t count)
{
	char	*next;
	char	*third;

	next = (char *)s + 1;
	third = (char *)s + 2;
	if (*next && is_redirect(*next) && (*next == *s))
	{
		if (*third && is_redirect(*third) && (*third == *s) && *third == '<')
		{
			if (count == 0)
				return (3);
			else
				return (count);
		}
		if (count == 0)
			return (2);
		else
			return (count);
	}
	if (count == 0)
		return (1);
	else
		return (count);
}

char const	*count_for_redirect(char const *s)
{
	char	*next;
	char	*third;

	next = (char *)s + 1;
	third = (char *)s + 2;
	if (*next && is_redirect(*next) && (*next == *s))
	{
		if (*third && is_redirect(*third) && (*third == *s) && *third == '<')
			s += 2;
		else
			s++;
	}
	return (s);
}

char	get_quote_trigger(char quote_trigger, char const *s)
{
	if (quote_trigger == 0)
	{
		if (*s == '\'' || *s == '\"')
			quote_trigger = *s;
	}
	else if (quote_trigger != 0)
	{
		if (*s == '\'' && quote_trigger == *s)
			quote_trigger = 0;
		if (*s == '\"' && quote_trigger == *s)
			quote_trigger = 0;
	}
	return (quote_trigger);
}
