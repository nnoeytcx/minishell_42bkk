/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:05:36 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/06 15:08:02 by tpoungla         ###   ########.fr       */
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

void	free_me(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free (res[i]);
		i++;
	}
	free (res);
}

int	ft_isspace(char c)
{
	if (c == '\r' || c == '\n' || c == '\f' )
		return (1);
	else if (c == '\v' || c == '\t' || c == ' ' )
		return (1);
	return (0);
}

int	is_meta(char c)
{
	if (c == '|' || c == '>' || c == '<' )
		return (1);
	return (0);
}

int	check_quote_close(const char *c)
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

int	ft_check_meta(const char *c)
{
	char	**res;
	char	temp;
	char	two;
	int		i;
	int		j;

	i = 0;
	two = 0;
	res = ft_split_sp(c, ' ');
	while (res[i])
	{
		j = 0;
		temp = res[i][0];
		if (i == 0 && temp == '|')
		{
			parser_error("|");
			free_me (res);
			//printf("[%c]\n", temp);
			return (0);// '|'
		}
		if (two)
		{
			//printf("[%c %c]\n", temp, two);
			if (is_meta(temp) && (two == '<' || two == '>'))
			{
				parser_error("|");
				free_me (res);
				//printf("[%c %c]\n", two, temp);
				return (0);// '|'
			}
		}
		while (res[i][j])
		{
			j++;
		}
		two = res[i][j - 1];
		i++;
	}
	if (is_meta(two))
	{
		//printf("[%c]\n", two);
		parser_error(NULL);
		free_me (res);
		return (0);// newline
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
