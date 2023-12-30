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
	char	*tmpstr;

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

char	*get_new_str(char *str)
{
	char	*new_str;

	new_str = "(your new str)";
	//new_str = get_value_from_key(str, )
	//if not found return null
	return (new_str);
}

int	is_submeta(char c)
{
	if (c == '\'' || c == '<' || c == '>' || c == '$')
		return (1);
	return (0);
}

char	*my_ft_strjoin(char const *s1, char c2)
{
	char	*j_str;
	char	*str_joined;

	j_str = malloc(ft_strlen(s1) + 2);
	if (!j_str)
		return (0);
	str_joined = j_str;
	while (*s1)
	{
		*j_str = *s1;
		s1++;
		j_str++;
	}
	*j_str = c2;
	j_str++;
	*j_str = '\0';
	return (str_joined);
}

char	*find_dollarsign(char *str)
{
	int		i;
	int		len;
	int		k;
	int		open;
	char	*new_str;
	char	*substr;
	char	*tmpstr;

	open = 0;
	i = 0;
	k = 0;
	len = 0;
	new_str = ft_strdup("");
	while (str[i])
	{
		len++;
		if (str[i] == '$')
		{
			if (open == 1 && len - 1)
			{
				substr = ft_substr(str, k, len - 1);
				tmpstr = get_new_str(substr);
				free(substr);
				substr = new_str;
				new_str = ft_strjoin(substr, tmpstr);
				free(substr);
			}
			open = 1;
			k = i + 1;
			len = 0;
		}
		if (is_submeta(str[i]) && len && open)
		{
			if (len - 1)
			{
				substr = ft_substr(str, k, len - 1);
				tmpstr = get_new_str(substr);
				free(substr);
				substr = new_str;
				new_str = ft_strjoin(substr, tmpstr);
				free(substr);
			}
			open = 0;
			len = 0;
		}
		if (open == 0)
		{
			tmpstr = new_str;
			new_str = my_ft_strjoin(tmpstr, str[i]);
			free(tmpstr);
		}
		i++;
	}
	if (len && open)
	{
		substr = ft_substr(str, k, len);
		tmpstr = get_new_str(substr);
		free(substr);
		substr = new_str;
		new_str = ft_strjoin(substr, tmpstr);
		free(substr);
	}
	return (new_str);
}

char	*get_expand(char *str_tab)
{
	char	*s;
	char	*tmpstr;
	char	*substr;
	char	tmp;
	int		i;
	int		len;
	int		k;
	char	*new_str;

	i = 0;
	k = 0;
	len = 0;
	tmp = 0;
	s = str_tab;
	new_str = ft_strdup("");
	while (s[i])
	{
		len++;
		if (is_quote(s[i]) && tmp == s[i])
		{
			if (len)
			{
				substr = ft_substr(s, k, len);
				tmpstr = find_dollarsign(substr);
				free(substr);
				substr = new_str;
				new_str = ft_strjoin(substr, tmpstr);
				free(tmpstr);
				free(substr);
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
					substr = ft_substr(s, k, len);
					tmpstr = find_dollarsign(substr);
					free(substr);
					substr = new_str;
					new_str = ft_strjoin(substr, tmpstr);
					free(tmpstr);
					free(substr);
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
		substr = ft_substr(s, k, len);
		tmpstr = find_dollarsign(substr);
		free(substr);
		substr = new_str;
		new_str = ft_strjoin(substr, tmpstr);
		free(tmpstr);
		free(substr);
	}
	return (new_str);
}

char	*trim_and_expand(char *str_tab)
{
	char	*s;
	char	tmp;
	char	*new_str;
	char	*tmpstr;
	char	*substr;
	int		i;
	int		len;
	int		k;

	i = 0;
	k = 0;
	len = 0;
	tmp = 0;
	s = str_tab;
	new_str = ft_strdup("");
	while (s[i])
	{
		len++;
		if (is_quote(s[i]) && tmp == s[i])
		{
			if (tmp == '\"')
			{
				substr = ft_substr(s, k + 1, len - 2);
				tmpstr = get_expand(substr);
				free(substr);
				substr = new_str;
				new_str = ft_strjoin(substr, tmpstr);
				free(tmpstr);
				free(substr);
			}
			else
			{
				if (len > 2)
				{
					substr = ft_substr(s, k + 1, len - 2);
					tmpstr = get_expand(substr);
					free(substr);
					substr = new_str;
					new_str = ft_strjoin(substr, tmpstr);
					free(substr);
					free(tmpstr);
				}
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
				substr = ft_substr(s, k, len);
				tmpstr = get_expand(substr);
				free(substr);
				substr = new_str;
				new_str = ft_strjoin(substr, tmpstr);
				free(substr);
				free(tmpstr);
				tmp = 0;
				len = 0;
				k = i + 1;
			}
		}
		i++;
	}
	if (len)
	{
		substr = ft_substr(s, k, len);
		tmpstr = get_expand(substr);
		free(substr);
		substr = new_str;
		new_str = ft_strjoin(substr, tmpstr);
		free(substr);
		free(tmpstr);
	}
	tmpstr = new_str;
	new_str = my_ft_strjoin(tmpstr, ' ');
	free(tmpstr);
	return (new_str);
}

int	main(void)
{
	int		i;
	int		len;
	char	**res;
	char	*substr;

	i = 0;
	printf("<< in cat ls -la << 'ls' < \"infile1\"  > putfile\n");
	res = ft_split_sp("<< in cat ls -la << 'ls' < \"infile1\"  > putfile", ' ');
	//"<< in cat ls -la << 'ls' < "infile1"  > putfile"
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \'this is \"$PATH1\"\'$PATH2\'$PATH3\'\n");
	res = ft_split_sp("echo \'this is \"$PATH1\"\'$PATH2\'$PATH3\'", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo for\"this is \'$PATH\' variable >> \"$PATH\"\">output\n");
	res = ft_split_sp("echo for\"this is \'$PATH\' variable >> \"$PATH\"\">output", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);



	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo for space \"this is \'$PATH\' variable >> \"$PATH\"\">output\n");
	res = ft_split_sp("echo for space \"this is \'$PATH\' variable >> \"$PATH\"\">output", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \'this is \'\"\'$PATH\'\"\'\'\n");
	res = ft_split_sp("echo \'this is \'\"\'$PATH\'\"\'\'", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \'this is \'\"\'$PATH\'\"\"\"\n");
	res = ft_split_sp("echo \'this is \'\"\'$PATH\'\"\"\"", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \'this is \'\"\'$PATH\'\"\"\"$PATH\n");
	res = ft_split_sp("echo \'this is \'\"\'$PATH\'\"\"\"$PATH", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo $PATHerete$PATH\n");
	res = ft_split_sp("echo $PATHerete$PATH", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"\'$PATH$PATH\'\"\n");
	res = ft_split_sp("echo \"\'$PATH$PATH\'\"", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \'\"$PATH$PATH\"\'\n");
	res = ft_split_sp("echo \'\"$PATH$PATH\"\'", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"\"$PATH$PATH\"\"\n");
	res = ft_split_sp("echo \"\"$PATH$PATH\"\"", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \'\'$PATH$PATH\'\'\n");
	res = ft_split_sp("echo \'\'$PATH$PATH\'\'", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"$PATH\'$PATH\"\n");
	res = ft_split_sp("echo \"$PATH\'$PATH\"", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"$PATH<<<<\"\n");
	res = ft_split_sp("echo \"$PATH<<<<\"", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"$\?\?<<<<\"\n");
	res = ft_split_sp("echo \"$\?\?<<<<\"", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"$\?$\?<<<<\"\n");
	res = ft_split_sp("echo \"$\?$\?<<<<\"", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"$$<<<<\"\n");
	res = ft_split_sp("echo \"$$<<<<\"", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"$$PATH<<<<\"\n");
	res = ft_split_sp("echo \"$$PATH<<<<\"", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"this is $PATH\'\'\"\'\'\n");
	res = ft_split_sp("echo \"this is $PATH\'\'\"\'\'", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"this is $PATH\'\'\"\n");
	res = ft_split_sp("echo \"this is $PATH\'\'\"", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);


	printf("\n--------------------------------------\n");
	i = 0;
	printf("echo \"this is $PATHPATH\"\n");
	res = ft_split_sp("echo \"this is $PATHPATH\"", ' ');
	while (res[i])
	{
		substr = trim_and_expand(res[i]);
		printf("%s", substr);
		free(substr);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}
