/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:17:13 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/08 20:47:11 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_close(int fd)
{
	if (fd == -1)
		return (-1);
	close(fd);
	return (-1);
}

int	count_command_tab(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		count;

	count = 0;
	tmp = cmd;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

int	str_n_compare(const char *s1, const char *s2, size_t n)
{
	while (n)
	{
		if (*s1 != *s2)
			return (0);
		if (*s1 == 0)
			return (0);
		n--;
		s1++;
		s2++;
	}
	return (1);
}
