/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:19:16 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 15:20:24 by pruenrua         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	err_cmd(int	*ecode, int errnum, char *cmd)
{
	if (errnum == 13 && find_slash(cmd))
	{
		ft_putstr_fd(strerror(errnum), 2);
		*ecode = 126;
	}
	else if (find_slash(cmd))
	{
		*ecode = 127;
		ft_putstr_fd("no such file or directory", 2);
	}
	else
	{
		*ecode = 127;
		ft_putstr_fd("command not found", 2);
	}
}

void	errorcmd(t_cmd *t_c, t_tok *t, int errnum)
{
	int	ecode;

	ecode = 1;
	ft_putstr_fd("minishell: ", 2);
	err_cmd(&ecode, errnum, t_c->command_line[0]);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(t_c->command_line[0], 2);
	ft_putstr_fd("\n", 2);
	free_token(t);
	printf("exit with ecode [%d]", ecode);
	exit(ecode);
}
