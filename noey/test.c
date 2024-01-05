#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include "../libft/libft.h"
#include "../header/minishell.h"

char	*find_dollarsign(char *str, t_env *env)
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
				tmpstr = get_new_str(substr, env);
				free(substr);
				substr = new_str;
				new_str = ft_strjoy(substr, tmpstr);
				free(substr);
				free(tmpstr);
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
				tmpstr = get_new_str(substr, env);
				free(substr);
				substr = new_str;
				new_str = ft_strjoy(substr, tmpstr);
				free(substr);
				free(tmpstr);
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
		tmpstr = get_new_str(substr, env);
		free(substr);
		substr = new_str;
		new_str = ft_strjoy(substr, tmpstr);
		free(tmpstr);
		free(substr);
	}
	return (new_str);
}

char	*get_expand(char *str_tab, t_env *env)
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
				tmpstr = find_dollarsign(substr, env);
				free(substr);
				substr = new_str;
				new_str = ft_strjoy(substr, tmpstr);
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
					tmpstr = find_dollarsign(substr, env);
					free(substr);
					substr = new_str;
					new_str = ft_strjoy(substr, tmpstr);
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
		tmpstr = find_dollarsign(substr, env);
		free(substr);
		substr = new_str;
		new_str = ft_strjoy(substr, tmpstr);
		free(tmpstr);
		free(substr);
	}
	return (new_str);
}

char	*trim_and_expand_heredoc(char *str_tab, t_env *env)
{
	char	*s;
	char	tmp;
	char	*new_str;
	char	*tmpstr;
	//char	*substr;
	int		i;
	int		num[2];

	i = 0;
	num[0] = 0;
	num[1] = 0;
	tmp = 0;
	s = str_tab;
	new_str = ft_strdup("");
	while (s[i])
	{
		num[0]++;
		if (is_quote(s[i]) && tmp == s[i])
		{
			if (tmp == '\"')
			{
				num[1] += 1;
				num[0] -= 2;
				tmpstr = new_str;
				new_str = my_ft_strjoin(tmpstr, '\"');
				free(tmpstr);
				new_str = get_newstr_expand(num, new_str, s, env);
				tmpstr = new_str;
				new_str = my_ft_strjoin(tmpstr, '\"');
				free(tmpstr);
				num[1] -= 1;
				num[0] += 2;
			}
			else
			{
				if (num[0] > 2)
				{
					num[1] += 1;
					num[0] -= 2;
					tmpstr = new_str;
					new_str = my_ft_strjoin(tmpstr, '\'');
					free(tmpstr);
					new_str = get_newstr_expand(num, new_str, s, env);
					tmpstr = new_str;
					new_str = my_ft_strjoin(tmpstr, '\'');
					free(tmpstr);
					num[1] -= 1;
					num[0] += 2;
				}
			}
			tmp = 0;
			num[0] = 0;
			num[1] = i + 1;
			i++;
			continue ;
		}
		if (is_quote(s[i]) && tmp == 0)
			tmp = s[i];
		if (!is_quote(s[i]) && tmp == 0)
		{
			if (s[i + 1] && is_quote(s[i + 1]))
			{
				new_str = get_newstr_expand(num, new_str, s, env);
				tmp = 0;
				num[0] = 0;
				num[1] = i + 1;
			}
		}
		i++;
	}
	if (num[0])
		new_str = get_newstr_expand(num, new_str, s, env);
	return (new_str);
}

int	main(void)
{
	char	**res;
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	res = ft_split_sp("echo \'this is \'\"\'PATH\'\"\'\'", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		printf("%s\n", trim_and_expand(res[i], env));
		i++;
	}

	i = 0;
	res = ft_split_sp("echo \'this is \'\"\'PATH\'\"\"\"", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		printf("%s\n", trim_and_expand(res[i], env));
		i++;
	}

	i = 0;
	res = ft_split_sp("echo \'this is \'\"\'PATH\'\"\"\"PATH", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		printf("%s\n", trim_and_expand(res[i], env));
		i++;
	}

	i = 0;
	res = ft_split_sp("\'echo \"this\" no\"is\" \'", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		printf("%s\n", trim_and_expand(res[i], env));
		i++;
	}

	i = 0;
	res = ft_split_sp("\"echo \'this is\' \"", ' ');
	while (res[i])
	{
		printf("[%s] ", res[i]);
		printf("%s\n", trim_and_expand(res[i], env));
		i++;
	}

}
