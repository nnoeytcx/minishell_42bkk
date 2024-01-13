/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:04:29 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/13 13:24:59 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	get_value_from_struct(t_strm *str_tab, t_tok *token)
{
	t_strm	*s;
	char	*str;

	s = str_tab;
	while (s)
	{
		str = s->value;
		str = trim_and_expand(str, token);
		free(s->value);
		s->value = str;
		s->type = string;
		s = s->next;
	}
	return (0);
}

void	init_arr_number(int *arr, int a, int b, int c)
{
	arr[0] = a;
	arr[1] = b;
	arr[2] = c;
	return ;
}

char	*find_dollarsign(char *str, t_tok *token)
{
	int		num[4];
	char	*new_str;
	char	*s;

	num[3] = -1;
	s = str;
	init_arr_number(num, 0, 0, 0);
	new_str = ft_strdup("");
	new_str = in_find(num, new_str, s, token);
	return (new_str);
}

char	*get_expand(char *str_tab, t_tok *token)
{
	char	*s;
	int		num[4];
	char	*new_str;

	num[3] = 0;
	init_arr_number(num, 0, 0, 0);
	s = str_tab;
	new_str = ft_strdup("");
	new_str = in_expand(num, new_str, s, token);
	return (new_str);
}

char	*trim_and_expand(char *str_tab, t_tok *token)
{
	char	*s;
	char	*new_str;
	int		num[4];

	num[3] = 0;
	init_arr_number(num, 0, 0, 0);
	s = str_tab;
	new_str = ft_strdup("");
	new_str = in_trim(num, new_str, s, token);
	return (new_str);
}
