/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:53:14 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 01:53:23 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_builtin(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (str_n_compare(cmd, "cd", len))
		return (1);
	if (str_n_compare(cmd, "echo", len))
		return (1);
	if (str_n_compare(cmd, "env", len))
		return (1);
	if (str_n_compare(cmd, "exit", len))
		return (1);
	if (str_n_compare(cmd, "export", len))
		return (1);
	if (str_n_compare(cmd, "pwd", len))
		return (1);
	if (str_n_compare(cmd, "unset", len))
		return (1);
	return (0);
}

int	run_builtin(char **cmd_lst, t_tok *token)
{
	int	len;

	len = ft_strlen(cmd_lst[0]);
	if (str_n_compare(cmd_lst[0], "cd", len))
		return (ft_cd(cmd_lst, token->env_token));
	if (str_n_compare(cmd_lst[0], "echo", len))
		return (ft_echo(cmd_lst));
	if (str_n_compare(cmd_lst[0], "env", len))
		return (ft_env(token->env_token));
	if (str_n_compare(cmd_lst[0], "exit", len))
		return (ft_exit(cmd_lst, token));
	if (str_n_compare(cmd_lst[0], "export", len))
		return (ft_export(cmd_lst, token));
	if (str_n_compare(cmd_lst[0], "pwd", len))
		return (ft_pwd(PRINT, cmd_lst));
	return (0);
}