
#include "../header/minishell.h"

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
