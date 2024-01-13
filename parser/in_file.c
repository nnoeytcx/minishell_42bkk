/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 13:31:09 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/13 20:56:06 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*get_join_c(char *new_str, char c)
{
	char	*tmp;

	tmp = new_str;
	new_str = my_ft_strjoin(tmp, c);
	free(tmp);
	return (new_str);
}

char	*in_find(int num[4], char *new_str, \
		char *str, t_tok *token)
{
	while (str[++num[3]])
	{
		num[1]++;
		if (str[num[3]] == '$')
		{
			if (num[2] == 1)
				new_str = new_str_find(str, num, token, new_str);
			init_arr_number(num, num[3] + 1, 0, 1);
		}
		if ((is_submeta(str[num[3]]) || ft_isspace(str[num[3]])) && num[1] \
				&& num[2])
		{
			new_str = new_str_find(str, num, token, new_str);
			init_arr_number(num, num[0], 0, 0);
		}
		if (num[2] == 0)
			new_str = get_join_c(new_str, str[num[3]]);
	}
	if (num[2])
		new_str = new_str_find2(str, num, token, new_str);
	return (new_str);
}

char	*in_expand(int num[4], char *new_str, \
		char *s, t_tok *token)
{
	while (s[num[3]])
	{
		num[1]++;
		if (is_quote(s[num[3]]) && num[2] == s[num[3]])
		{
			new_str = new_str_getex(s, num, token, new_str);
			init_arr_number(num, num[3] + 1, 0, 0);
			num[3]++;
			continue ;
		}
		check_open_q(s[num[3]], num);
		if (!is_quote(s[num[3]]) && num[2] == 0)
		{
			if (s[num[3] + 1] && is_quote(s[num[3] + 1]))
			{
				new_str = new_str_getex(s, num, token, new_str);
				init_arr_number(num, num[3] + 1, 0, 0);
			}
		}
		num[3]++;
	}
	new_str = new_str_getex(s, num, token, new_str);
	return (new_str);
}

char	*in_trim(int num[4], char *new_str, \
		char *s, t_tok *token)
{
	while (s[num[3]])
	{
		num[0]++;
		if (is_quote(s[num[3]]) && num[2] == s[num[3]])
		{
			if (num[2] == '\"')
				new_str = get_newstr_expand(num, new_str, s, token);
			if (num[0] > 2 && num[2] == '\'')
				new_str = joy_str(s, num, new_str);
			init_arr_number(num, 0, num[3] + 1, 0);
			num[3]++;
			continue ;
		}
		check_open_q(s[num[3]], num);
		if ((!is_quote(s[num[3]]) && num[2] == 0) && \
			(s[num[3] + 1] && is_quote(s[num[3] + 1])))
		{
			new_str = get_newstr_expand(num, new_str, s, token);
			init_arr_number(num, 0, num[3] + 1, 0);
		}
		num[3]++;
	}
	if (num[0])
		new_str = get_newstr_expand(num, new_str, s, token);
	return (new_str);
}
