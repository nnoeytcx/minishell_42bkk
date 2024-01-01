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

int	ft_isspace(char c)
{
	if (c == '\r' || c == '\n' || c == '\f' )
		return (1);
	else if (c == '\v' || c == '\t' || c == ' ' )
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	check_quote_meta(const char *c)
{
	char	qt;

	qt = 0;
	while (*c)
	{
		qt = get_quote_trigger(qt, c);
		c++;
	}
	if (qt != 0)
		return (0);
	return (1);
}

int	check_no_space(const char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!ft_isspace(c[i]))
			i++;
		else
			return (0);
	}
	if (i == 0)
		return (0);
	return (1);
}

int	is_good_input(const char *c)
{
	if (!check_no_space(c))
		return (0);
	if (!check_quote_meta(c))
		return (0);
	return (1);
}

int	main(void)
{
	char	*res;

	res = "     	 	 ";
	printf("%s [%d]\n", res, is_good_input(res));
	res = "				";
	printf("%s [%d]\n", res, is_good_input(res));
	res = "    ";
	printf("%s [%d]\n", res, is_good_input(res));
	res = "";
	printf("%s [%d]\n", res, is_good_input(res));
	res = "\'";
	printf("%s [%d]\n", res, is_good_input(res));
	res = "\"";
	printf("%s [%d]\n", res, is_good_input(res));
	res = "\'\'";
	printf("%s [%d]\n", res, is_good_input(res));
	res = "\"\"";
	printf("%s [%d]\n", res, is_good_input(res));
	res = "\'\"\'";
	printf("%s [%d]\n", res, is_good_input(res));
	res = "\"\'\"";
	printf("%s [%d]\n", res, is_good_input(res));

	// res = "echo \'this is \'\"\'$PATH\'\"\'\'";
	// printf("%s %d\n", res, is_good_input(res));
	// res = "echo \'this is \'\"\'$PATH\'\"\"\"";
	// printf("%s %d\n", res, is_good_input(res));
	// res = "echo \'this is \'\"\'$PATH\'\"\"\"$PATH";
	// printf("%s %d\n", res, is_good_input(res));
	// res = "echo $PATHerete$PATH";
	// printf("%s %d\n", res, is_good_input(res));
	// res = "echo \"\'$PATH$PATH\'\"";
	// printf("%s %d\n", res, is_good_input(res));
	// res = "echo \'\"$PATH$PATH\"\'";
	// printf("%s\n", res);
	// res = "echo \"\"$PATH$PATH\"\"";
	// printf("%s\n", res);
	// res = "echo \'\'$PATH$PATH\'\'";
	// printf("%s\n", res);
	// res = "echo \"$PATH\'$PATH\"";
	// printf("%s\n", res);
	// res = "echo \"$PATH<<<<\"";
	// printf("%s\n", res);
	// res = "echo \"$\?\?<<<<\"";
	// printf("%s\n", res);
	// res = "echo \"$\?$\?<<<<\"";
	// printf("%s\n", res);
	// res = "echo \"$$<<<<\"";
	// printf("%s\n", res);
	// res = "echo \"$$PATH<<<<\"";
	// printf("%s\n", res);
	// res = "echo \"this is $PATH\'\'\"\'\'";
	// printf("%s\n", res);
	// res = "echo \"this is $PATH\'\'\"";
	// printf("%s\n", res);
	// res = "echo \"this is $PATHPATH\"";
	// printf("%s\n", res);
}
