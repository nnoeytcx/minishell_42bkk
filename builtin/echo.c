/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:32:28 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/13 12:46:37 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_echo(char **param)
{
	int	option;
	int	i;

	i = 0;
	option = 0;
	while (param[i])
		i++;
	i = 1;
	while (param[i] && is_same_str(param[i], "-n"))
	{
		option = 1;
		i++;
	}
	while (param[i])
	{
		ft_putstr_fd(param[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (option != 1)
		printf("\n");

	return (0);
}
