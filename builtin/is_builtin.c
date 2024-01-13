/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:53:14 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/14 01:52:36 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_same_str(char *s1, char *s2)
{
	int	ret;

	ret = 1;
	if (!s1 || !s2)
		return (0);
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			ret = 0;
		s2++;
		s1++;
	}
	if (*s1 != '\0' || *s2 != '\0')
		ret = 0;
	return (ret);
}

int	command_is_builtin(t_cmd *t_c)
{
	char	**cmd;
	int		ret;

	ret = 0;
	cmd = get_cmd(t_c->str_mode);
	if (is_builtin(cmd[0]))
		ret = 1;
	cmd = free2d(cmd);
	return (ret);
}

int	command_is_sin_builtin(t_cmd *t_c)
{
	char	**cmd;
	int		ret;

	ret = 0;
	cmd = get_cmd(t_c->str_mode);
	if (is_sin_builtin(cmd[0]))
		ret = 1;
	cmd = free2d(cmd);
	return (ret);
}

int	is_sin_builtin(char *cmd)
{
	if (is_same_str(cmd, "cd"))
		return (1);
	if (is_same_str(cmd, "env"))
		return (1);
	if (is_same_str(cmd, "exit"))
		return (1);
	if (is_same_str(cmd, "export"))
		return (1);
	if (is_same_str(cmd, "unset"))
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (is_same_str(cmd, "cd"))
		return (1);
	if (is_same_str(cmd, "echo"))
		return (1);
	if (is_same_str(cmd, "env"))
		return (1);
	if (is_same_str(cmd, "exit"))
		return (1);
	if (is_same_str(cmd, "export"))
		return (1);
	if (is_same_str(cmd, "pwd"))
		return (1);
	if (is_same_str(cmd, "unset"))
		return (1);
	return (0);
}
