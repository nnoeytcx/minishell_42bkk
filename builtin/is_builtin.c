/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:53:14 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/07 02:03:37 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_same_str(char *s1, char *s2)
{
	int	ret;

	ret = 1;
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

int	run_single_builtin(t_tok *t)
{
	int		ret;

	t->command->command_line = get_cmd(t->command->str_mode);
	ret = 0;
	ret = run_builtin(t->command->command_line, t);
	return (ret);
}

int	run_builtin(char **cmd_lst, t_tok *token)
{
	if (is_same_str(cmd_lst[0], "cd"))
		return (ft_cd(cmd_lst, token));
	if (is_same_str(cmd_lst[0], "echo"))
		return (ft_echo(cmd_lst));
	if (is_same_str(cmd_lst[0], "env"))
		return (ft_env(token->env_token));
	if (is_same_str(cmd_lst[0], "exit"))
		return (ft_exit(cmd_lst, token));
	if (is_same_str(cmd_lst[0], "export"))
		return (ft_export(cmd_lst, token));
	if (is_same_str(cmd_lst[0], "pwd"))
		return (ft_pwd(PRINT, cmd_lst, token));
	if (is_same_str(cmd_lst[0], "unset"))
		return (ft_unset(cmd_lst, token));
	return (0);
}