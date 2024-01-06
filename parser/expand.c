/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:04:29 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/06 17:01:09 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	expand_from_env(t_strm *str_tab, t_env *env)
{
	t_strm	*s;
	t_env	*e;
	char	*env_str;

	e = env;
	s = str_tab;
	while (s)
	{
		if (s->type == variable && !ft_strncmp(s->value, "$", 1))
		{
			env_str = get_value_from_key((s->value + 1), e);
			free (s->value);
			s->value = env_str;
			s->type = string;
		}
		s = s->next;
	}
	return (0);
}

int	get_value_from_struct(t_strm *str_tab, t_tok *token)
{
	t_strm	*s;
	char	*str;

	s = str_tab;
	while (s)
	{
		str = s->value;
		printf("tab : {%s}\n", str);
		str = trim_and_expand(str, token);
		free(s->value);
		printf("new : %s\n", str);
		s->value = str;
		s->type = string;
		s = s->next;
	}
	return (0);
}
char	*find_dollarsign(char *str, t_tok *token)
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
				tmpstr = get_new_str(substr, token);
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
				tmpstr = get_new_str(substr, token);
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
		tmpstr = get_new_str(substr, token);
		free(substr);
		substr = new_str;
		new_str = ft_strjoy(substr, tmpstr);
		free(tmpstr);
		free(substr);
	}
	return (new_str);
}

char	*get_expand(char *str_tab, t_tok *token)
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
				tmpstr = find_dollarsign(substr, token);
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
					tmpstr = find_dollarsign(substr, token);
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
		tmpstr = find_dollarsign(substr, token);
		free(substr);
		substr = new_str;
		new_str = ft_strjoy(substr, tmpstr);
		free(tmpstr);
		free(substr);
	}
	return (new_str);
}

char	*trim_and_expand(char *str_tab, t_tok *token)
{
	char	*s;
	char	tmp;
	char	*new_str;
	char	*tmpstr;
	char	*substr;
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
				new_str = get_newstr_expand(num, new_str, s, token);
				num[1] -= 1;
				num[0] += 2;
			}
			else
			{
				if (num[0] > 2)
				{
					tmpstr = ft_substr(s, num[1] + 1, num[0] - 2);
					substr = new_str;
					new_str = ft_strjoy(substr, tmpstr);
					free(substr);
					free(tmpstr);
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
				new_str = get_newstr_expand(num, new_str, s, token);
				tmp = 0;
				num[0] = 0;
				num[1] = i + 1;
			}
		}
		i++;
	}
	if (num[0])
		new_str = get_newstr_expand(num, new_str, s, token);
	return (new_str);
}
