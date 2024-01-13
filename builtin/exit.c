/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:52:56 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/14 01:29:00 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	put_err_cd(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

size_t	ft_atoll_check(const char *str, int mode)
{
	int		lob;
	size_t	result;

	result = 0;
	lob = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			lob = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (mode == 1)
	{
		if ((result > 9223372036854775807 && lob == 1) \
					|| (result > 9223372036854775808ULL && lob == -1))
			return (0);
	}
	return ((size_t)(result * lob));
}

int	is_param_numeric(char *param)
{
	int	i;

	i = 0;
	if (param[i] == '+' || param[i] == '-')
		i++;
	while (param[i])
	{
		if (!ft_isdigit(param[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **param, t_tok *token, int in)
{
	size_t	status;
	int		i;

	i = 0;
	while (param[i])
		i++;
	if (in == 0)
		ft_putstr_fd("exit\n", 1);
	if (i > 2 && is_param_numeric(param[1]))
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 2);
	if (i == 1)
		status = 0;
	else if (!is_param_numeric(param[1]) || 0 == ft_atoll_check(param[1], 1))
	{
		put_err_cd(param[1]);
		status = 255;
	}
	else
		status = ft_atoll_check(param[1], 0);
	free_token(token);
	exit(status % 256);
}
