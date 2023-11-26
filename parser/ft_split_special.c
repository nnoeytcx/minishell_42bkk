#include "../header/minishell.h"

size_t	ccount_on_me(char const *s, char c)
{
	int	word;
	int	skip;
    int quote_trigger[2];

    quote_trigger[0] = 0;
    quote_trigger[1] = 0;
	skip = 0;
	word = 0;
	while (*s)
	{
        if (*s == '\"')
        {
            if (quote_trigger[1] == 1)
                quote_trigger[1] = 0;
            else
                quote_trigger[1] = 1;
        }
        if (*s == '\'')
        {
            if (quote_trigger[0] == 1)
                quote_trigger[0] = 0;
            else
                quote_trigger[0] = 1;
        }
        if (*s == c && skip == 1 && quote_trigger[1] == 0 && quote_trigger[0] == 0)
			skip = 0;
		if (*s != c && skip == 0 && quote_trigger[1] == 0 && quote_trigger[0] == 0)
		{
			word++;
			skip = 1;
		}
		s++;
	}
    printf("word = [%d]\n", word);
	return (word);
}

size_t	hhow_long(char const *s, char c)
{
	size_t	count;
    int     quote_trigger[2];

    quote_trigger[0] = 0;
    quote_trigger[1] = 0;
	count = 0;
	while (*s)
	{
        if (*s == '\"')
        {
            if (quote_trigger[1] == 1)
                quote_trigger[1] = 0;
            else
                quote_trigger[1] = 1;
        }
        if (*s == '\'')
        {
            if (quote_trigger[0] == 1)
                quote_trigger[0] = 0;
            else
                quote_trigger[0] = 1;
        }
		if (*s == c && quote_trigger[1] == 0 && quote_trigger[0] == 0)
			return (count);
		count++;
		s++;
	}
    printf("count = [%d]\n", count);
	return (count);
}

char	**ft_split_sp(char const *s, char c)
{
	char	**resplit;
	size_t	i;
	size_t	big_i;

	if (!s)
		return (0);
	i = 0;
	big_i = 0;
    int word = ccount_on_me(s,c);
	resplit = (char **)malloc((sizeof(char *)) * (word + 1));
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
