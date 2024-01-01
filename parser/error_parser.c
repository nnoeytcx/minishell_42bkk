/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:05:36 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/01 01:00:26 by tpoungla         ###   ########.fr       */
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

int	ft_isspace(char c)
{
	if (c == '\r' || c == '\n' || c == '\f' )
		return (1);
	else if (c == '\v' || c == '\t' || c == ' ' )
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
			return (1);
		i++;
	}
	return (0);
}

int	is_good_input(const char *c)
{
	if (!check_no_space(c))
		return (0);
	if (!check_quote_meta(c))
		return (0);
	return (1);
}
