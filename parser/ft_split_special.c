#include "../header/minishell.h"

size_t	ccount_on_me(char const *s, char c)
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
	char	*next;
	char	*third;

	quote_trigger = 0;
	count = 0;
	while (*s)
	{
		quote_trigger = get_quote_trigger(quote_trigger, s);
		if (*s == c && quote_trigger == 0)
			return (count);
		if (is_redirect(*s) && quote_trigger == 0)
		{
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
	//printf("(%d)-------", word);
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
