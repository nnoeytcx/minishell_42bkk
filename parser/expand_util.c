/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:32:49 by tpoungla          #+#    #+#             */
/*   Updated: 2023/12/30 17:41:37 by tpoungla         ###   ########.fr       */
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

char	*get_new_str(char *str, t_env *env)
{
	char	*new_str;
	t_env	*e;

	new_str = NULL;
	e = env;
	new_str = get_value_from_key(str, e);
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
