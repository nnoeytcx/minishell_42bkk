/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:32:49 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/13 13:21:47 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*ft_strjoy(char const *s1, char const *s2)
{
	char	*j_str;
	char	*str_joined;

	if (!s2)
		return (ft_strdup(s1));
	j_str = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!j_str)
		return (0);
	str_joined = j_str;
	while (*s1)
	{
		*j_str = *s1;
		s1++;
		j_str++;
	}
	while (*s2)
	{
		*j_str = *s2;
		s2++;
		j_str++;
	}
	*j_str = '\0';
	return (str_joined);
}

char	*get_new_str(char *str, t_tok *token)
{
	char	*new_str;
	char	*tmpstr;
	char	*substr;
	t_env	*e;

	new_str = NULL;
	e = token->env_token;
	if (str[0] == '?')
	{
		tmpstr = ft_itoa(token->return_code);
		substr = ft_substr(str, 1, ft_strlen(str) - 1);
		new_str = ft_strjoy(tmpstr, substr);
		free(tmpstr);
		free(substr);
	}
	else
		new_str = get_value_from_key(str, e);
	return (new_str);
}

int	is_submeta(char c)
{
	if (c == '\'' || c == '<' || c == '>' || c == '$')
		return (1);
	return (0);
}

char	*my_ft_strjoin(char *s1, char c2)
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

void	check_open_q(char c, int *num)
{
	if (is_quote(c) && num[2] == 0)
		num[2] = c;
	return ;
}
