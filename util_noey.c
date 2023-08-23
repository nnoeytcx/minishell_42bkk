#include <stdlib.h>
#include <stdio.h>

int	ft_isspace(char c)
{
	if (c == '\r' || c == '\n' || c == '\f' )
		return (1);
	else if (c == '\v' || c == '\t' || c == ' ' )
		return (1);
	return (0);
}

void	ft_get_str(char const *s, char **res)
{
	int	i;
	int	m;
	int	n;

	i = 0;
	m = 0;
	n = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]) && s[i])
		{
			res[m][n] = s[i];
			n++;
		}
		if (!ft_isspace(s[i]) && (ft_isspace(s[i + 1]) || s[i + 1] == '\0'))
		{
			res[m][n] = '\0';
			m++;
			n = 0;
		}
		i++;
	}
	res[m] = NULL;
}

void	ft_get_tab(char const *s, char **res)
{
	int	i;
	int	m;
	int	n;

	n = 0;
	m = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]) && s[i])
			n++;
		if (!ft_isspace(s[i]) && (ft_isspace(s[i + 1]) || s[i + 1] == '\0'))
		{
			res[m] = malloc(sizeof(char) * (n + 1));
			if (!res[m])
			{
				while (res[m])
					free(res[m--]);
			}
			m++;
			n = 0;
		}
		i++;
	}
}

char	**ft_split(char *s)
{
	int		i;
	int		co;
	char	**res;

	co = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (!ft_isspace(s[i]) && (ft_isspace(s[i + 1]) || s[i + 1] == '\0'))
			co++;
		i++;
	}
	res = (char **)malloc(sizeof(char *) * (co + 1));
	if (!res)
		return (NULL);
	ft_get_tab(s, res);
	ft_get_str(s, res);
	return (res);
}