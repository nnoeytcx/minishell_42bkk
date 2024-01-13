/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 01:52:11 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/14 02:00:21 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	run_single_builtin(t_tok *t)
{
	int		ret;

	t->command->command_line = get_cmd(t->command->str_mode);
	ret = 0;
	ret = run_builtin(t->command->command_line, t, 0);
	return (ret);
}

int	run_builtin(char **cmd_lst, t_tok *token, int n)
{
	token->env = free2d(token->env);
	if (is_same_str(cmd_lst[0], "cd"))
		return (ft_cd(cmd_lst, token));
	if (is_same_str(cmd_lst[0], "echo"))
		return (ft_echo(cmd_lst));
	if (is_same_str(cmd_lst[0], "env"))
		return (ft_env(token->env_token));
	if (is_same_str(cmd_lst[0], "exit"))
		return (ft_exit(cmd_lst, token, n));
	if (is_same_str(cmd_lst[0], "export"))
		return (ft_export(cmd_lst, token));
	if (is_same_str(cmd_lst[0], "pwd"))
		return (ft_pwd(PRINT, cmd_lst, token));
	if (is_same_str(cmd_lst[0], "unset"))
		return (ft_unset(cmd_lst, token));
	return (0);
}
