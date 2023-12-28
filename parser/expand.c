/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:04:29 by tpoungla          #+#    #+#             */
/*   Updated: 2023/12/26 15:32:08 by tpoungla         ###   ########.fr       */
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

// int	get_value_from_struct(t_strm *str_tab)
// {
// 	t_strm	*s;
// 	char	*str;

// 	s = str_tab;
// 	while (s)
// 	{
// 		str = s->value;
// 		trim_and_expand(str);
// 		s = s->next;
// 	}
// 	return (0);
// }
