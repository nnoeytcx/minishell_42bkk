#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include "../libft/libft.h"

#define META_CHAR "> >> < << <<< | && & $ "
int	is_redirect(char c)
{
	if (c == '>' || c == '<')
		return (1);
	else
		return (0);
}

size_t	ccount_on_me(char const *s, char c)
{
	int		word;
	int		skip;
	char	quote_trigger;
	char	*next;
	char	*third;

	quote_trigger = 0;
	skip = 0;
	word = 0;
	while (*s)
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
		if (*s == c && skip == 1 && quote_trigger == 0)
			skip = 0;
		if (*s != c && skip == 0 && !is_redirect(*s))
		{
			word++;
			skip = 1;
		}
		if (is_redirect(*s))
		{
			if (skip == 1)
				skip = 0;
			word++;

			next = (char *)s+1;
			third = (char *)s+2;
			if (*next && is_redirect(*next) && (*next == *s))
			{
				if (*third && is_redirect(*third) && (*third == *s) && *third == '<')
					s+=2;
				else
					s++;
			}
			//printf("[%c]\n", *next);
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
	char	*next;
	char	*third;

	quote_trigger = 0;
	count = 0;
	while (*s)
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
		if (*s == c && quote_trigger == 0)
			return (count);
		if (is_redirect(*s) && quote_trigger == 0)
		{
			next = (char *)s+1;
			third = (char *)s+2;
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
		count++;
		s++;
	}
	return (count);
}

char	**ft_split_sp(char const *s, char c)
{
	char	**resplit;
	size_t	i;
	size_t	big_i;
	int		word;

	if (!s)
		return (0);
	i = 0;
	big_i = 0;
	word = ccount_on_me(s, c);
	printf("(%d)-------", word);
	if (word == -1)
		return (printf("fatal error the quote must close properly!!!!! thx\n"), NULL);
	resplit = ft_calloc((sizeof(char *)), (word + 1));
	if (!resplit)
		return (0);
	while (s[i] && i <= ft_strlen(s))
	{
		if (s[i] != c)
		{
			resplit[big_i] = ft_substr(s, i, hhow_long(&s[i], c));
			i = i + hhow_long(&s[i], c);
			big_i++;
		}
		if (s[i] == c)
			i++;
	}
	resplit[big_i] = NULL;
	return (resplit);
}

int	main(void)
{
	int		i;
	char	**res;

	i = 0;
	printf("---------------BASIC TEST---------------\n");
	printf("yayyou i know\n");
	res = ft_split_sp("yayyou i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf("yay>you i know\n");
	res = ft_split_sp("yay>you i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf(">you i know\n");
	res = ft_split_sp(">you i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf("yay> i know\n");
	res = ft_split_sp("yay> i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}

	i = 0;
	printf("\n---------------SECOND TEST---------------\n");
	printf("yay>>you i know\n");
	res = ft_split_sp("yay>>you i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf(">>you i know\n");
	res = ft_split_sp(">>you i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf("yay>> i know\n");
	res = ft_split_sp("yay>> i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}

	i = 0;
	printf("\n---------------THIRD TEST---------------\n");
	printf("yay>>>you i know\n");
	res = ft_split_sp("yay>>>you i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf(">>>you i know\n");
	res = ft_split_sp(">>>you i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf("yay>>> i know\n");
	res = ft_split_sp("yay>>> i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}

	i = 0;
	printf("\n---------------N MORE TEST---------------\n");
	printf("yay>>>>>you i know\n");
	res = ft_split_sp("yay>>>>>you i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf(">>>>you i know\n");
	res = ft_split_sp(">>>>you i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf("yay>>>>>> i know\n");
	res = ft_split_sp("yay>>>>>> i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}

	i = 0;
	printf("\n---------------BASIC MIX TEST---------------\n");
	printf("yay<>you i know\n");
	res = ft_split_sp("yay<>you i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf("><you i know\n");
	res = ft_split_sp("><you i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf("yay<> i know\n");
	res = ft_split_sp("yay<> i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}

	i = 0;
	printf("\n---------------MORE MIX TEST---------------\n");
	printf("yay><<>you i know\n");
	res = ft_split_sp("yay><<>you i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf("><<you i know\n");
	res = ft_split_sp("><<you i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf("yay<<> i know\n");
	res = ft_split_sp("yay<<> i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}

	i = 0;
	printf("\n---------------CRAZY MIX TEST---------------\n");
	printf("yay><<<><>you i know\n");
	res = ft_split_sp("yay><<<><>you i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf("><><<you i know\n");
	res = ft_split_sp("><><<you i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
	i = 0;
	printf("\n");
	printf("yay><<<<><<> i know\n");
	res = ft_split_sp("yay><<<<><<> i know", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		i++;
	}
}
