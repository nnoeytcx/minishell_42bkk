#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include "../libft/libft.h"

#define META_CHAR "> >> < << <<< | && & $"

int	is_redirect(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
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
	if (word == -1)
		return (NULL);
	resplit = ft_calloc((sizeof(char *)), (word + 1));
	if (!resplit)
		return (0);
	resplit = gget_split(s, c, resplit);
	return (resplit);
}

// char	*expand_from_env(char *str, t_env *env)
// {
// 	t_env	*e;
// 	char	*env_str;
// 	char	*tmp_str;
// 	int		i;

// 	i = 0;
// 	e = env;
// 	s = str_tab;
// 	tmp_str = "temp string";
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			env_str = tmp_str;
// 			//get_value_from_key((s->value + 1), e);
// 		i++;
// 	}
// 	return (env_str);
// }

int	is_submeta(char c)
{
	if (c == '\'' || c == '<' || c == '>' || c == '$')
		return (1);
	return (0);
}

int	find_dollarsign(char *str)
{
	int	i;
	int	len;
	int	k;
	int	open;

	open = 0;
	i = 0;
	k = 0;
	len = 0;
	//printf(" word = (%s)", str);
	while (str[i])
	{
		len++;
		if (str[i] == '$')
		{
			if (open == 1)
			{
				printf("|%s|", ft_substr(str, k, len - 1));
			}
			open = 1;
			k = i + 1;
			len = 0;
		}
		if (is_submeta(str[i]) && len && open)
		{
			printf("|%s|", ft_substr(str, k, len - 1));
			open = 0;
			len = 0;
		}
		if (open == 0)
			printf("%c", str[i]);
		i++;
	}
	if (len && open)
	{
		printf("|%s|", ft_substr(str, k, len));
	}
	return (0);
}

void	get_expand(char *str_tab)
{
	char	*s;
	char	tmp;
	int		i;
	int		len;
	int		k;

	i = 0;
	k = 0;
	len = 0;
	tmp = 0;
	s = str_tab;
	while (s[i])
	{
		len++;
		if (is_quote(s[i]) && tmp == s[i])
		{
			if (len)
			{
				printf("\n[%s]", ft_substr(s, k, len));
				find_dollarsign(ft_substr(s, k, len));
			}
			tmp = 0;
			len = 0;
			k = i + 1;
			i++;
			continue ;
		}
		if (is_quote(s[i]) && tmp == 0)
			tmp = s[i];
		if (!is_quote(s[i]) && tmp == 0)
		{
			if (s[i + 1] && is_quote(s[i + 1]))
			{
				if (len)
				{
					printf("\n[%s]", ft_substr(s, k, len));
					find_dollarsign(ft_substr(s, k, len));
				}
				tmp = 0;
				len = 0;
				k = i + 1;
			}
		}
		i++;
	}
	if (len)
	{
		printf("\n[%s]", ft_substr(s, k, len));
		find_dollarsign(ft_substr(s, k, len));
	}
}

void	trim_and_expand(char *str_tab)
{
	char	*s;
	char	tmp;
	int		i;
	int		len;
	int		k;

	i = 0;
	k = 0;
	len = 0;
	tmp = 0;
	s = str_tab;
	while (s[i])
	{
		len++;
		if (is_quote(s[i]) && tmp == s[i])
		{
			if (tmp == '\"')
				get_expand(ft_substr(s, k + 1, len - 2));
			else
			{
				if (len > 2)
					printf("\n{%s} ", ft_substr(s, k + 1, len - 2));
			}
			tmp = 0;
			len = 0;
			k = i + 1;
			i++;
			continue ;
		}
		if (is_quote(s[i]) && tmp == 0)
			tmp = s[i];
		if (!is_quote(s[i]) && tmp == 0)
		{
			if (s[i + 1] && is_quote(s[i + 1]))
			{
				get_expand(ft_substr(s, k, len));
				tmp = 0;
				len = 0;
				k = i + 1;
			}
		}
		i++;
	}
	if (len)
		get_expand(ft_substr(s, k, len));
}

int	main(void)
{
	int		i;
	int		len;
	char	**res;

	i = 0;
	printf("echo \"this is \"$PATH1\"\'$PATH2\'$PATH3\"\n");
	res = ft_split_sp("echo \"this is \"$PATH1\"\'$PATH2\'$PATH3\"", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \'this is \"$PATH1\"\'$PATH2\'$PATH3\'\n");
	res = ft_split_sp("echo \'this is \"$PATH1\"\'$PATH2\'$PATH3\'", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo for\"this is \'$PATH\' variable >> \"$PATH\"\">output\n");
	res = ft_split_sp("echo for\"this is \'$PATH\' variable >> \"$PATH\"\">output", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo for space \"this is \'$PATH\' variable >> \"$PATH\"\">output\n");
	res = ft_split_sp("echo for space \"this is \'$PATH\' variable >> \"$PATH\"\">output", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \'this is \'\"\'$PATH\'\"\'\'\n");
	res = ft_split_sp("echo \'this is \'\"\'$PATH\'\"\'\'", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \'this is \'\"\'$PATH\'\"\"\"\n");
	res = ft_split_sp("echo \'this is \'\"\'$PATH\'\"\"\"", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \'this is \'\"\'$PATH\'\"\"\"$PATH\n");
	res = ft_split_sp("echo \'this is \'\"\'$PATH\'\"\"\"$PATH", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo $PATHerete$PATH\n");
	res = ft_split_sp("echo $PATHerete$PATH", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"\'$PATH$PATH\'\"\n");
	res = ft_split_sp("echo \"\'$PATH$PATH\'\"", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \'\"$PATH$PATH\"\'\n");
	res = ft_split_sp("echo \'\"$PATH$PATH\"\'", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"\"$PATH$PATH\"\"\n");
	res = ft_split_sp("echo \"\"$PATH$PATH\"\"", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \'\'$PATH$PATH\'\'\n");
	res = ft_split_sp("echo \'\'$PATH$PATH\'\'", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"$PATH\'$PATH\"\n");
	res = ft_split_sp("echo \"$PATH\'$PATH\"", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"$PATH<<<<\"\n");
	res = ft_split_sp("echo \"$PATH<<<<\"", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
		printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"$\?\?<<<<\"\n");
	res = ft_split_sp("echo \"$\?\?<<<<\"", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
		printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"$\?$\?<<<<\"\n");
	res = ft_split_sp("echo \"$\?$\?<<<<\"", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
	i = 0;
	printf("echo \"$$<<<<\"\n");
	res = ft_split_sp("echo \"$$<<<<\"", ' ');
	while (res[i])
	{
		trim_and_expand(res[i]);
		i++;
	}
}
