/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:05:36 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/07 03:43:58 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	parser_error(char *str)
{
	if (!str)
	{
		ft_putstr_fd(SYNTAX_ERR, 2);
		ft_putstr_fd("newline'\n", 2);
	}
	else
	{
		ft_putstr_fd(SYNTAX_ERR, 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (-1);
}

int	parser_error2(char c)
{
	ft_putstr_fd(SYNTAX_ERR, 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	return (-1);
}

int	ft_check_meta(const char *c)
{
	char	**res;
	char	two;
	int		i;
	int		j;

	i = 0;
	two = 0;
	res = ft_split_sp(c, ' ');
	while (res[i])
	{
		if (!in_check_meta(res, i, two))
			return (0);
		j = ft_strlen(res[i]);
		two = res[i][j - 1];
		i++;
	}
	if (is_meta(two))
	{
		parser_error(NULL);
		free_me (res);
		return (0);
	}
	free_me (res);
	return (1);
}

int	is_good_input(const char *c)
{
	if (!check_no_space(c))
		return (0);
	if (!check_quote_close(c))
		return (0);
	if (!ft_check_meta(c))
		return (0);
	return (1);
}
