/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:32:28 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/12 20:07:04 by pruenrua         ###   ########.fr       */
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
	while (param[i] && str_n_compare(param[i], "-n", ft_strlen(param[i])))
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