/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_and_parent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:25:44 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/14 03:56:56 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	term_error(int exit_st)
{
	int	exit_status;

	exit_status = 1;
	if (exit_st == 3)
	{
		ft_putstr_fd("QUIT : ", 2);
		ft_putnbr_fd(exit_st, 2);
		ft_putchar_fd('\n', 2);
		exit_status = 131;
	}
	else
		exit_status = 130;
	return (exit_status);
}

void	parent_prepare_next_command(t_cmd *cur_cmd, int pipo[2], int *tmp_fd)
{
	close(*tmp_fd);
	if (cur_cmd->next)
	{
		*tmp_fd = pipo[0];
		close(pipo[1]);
	}
}

int	wait_all_child(t_cmd *cmd_tab)
{
	t_cmd	*cmd_tab_t;
	int		exit_status;

	exit_status = 1;
	cmd_tab_t = cmd_tab;
	while (cmd_tab_t)
	{
		waitpid(cmd_tab_t->process_id, &exit_status, WUNTRACED);
		if (WIFSIGNALED(exit_status))
			exit_status = term_error(exit_status);
		else
			exit_status = WEXITSTATUS(exit_status);
		if (cmd_tab_t->process_status == -1)
			cmd_tab_t->process_status = exit_status;
		cmd_tab_t = cmd_tab_t->next;
	}
	setsig_exe(0);
	return (exit_status);
}

void	child_process_run(t_tok *t, t_cmd *cur_cmdtab, int pipo[2], int fd_in)
{
	setsig_exe(3);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	if (cur_cmdtab->next)
	{
		close(pipo[0]);
		dup2(pipo[1], STDOUT_FILENO);
		close(pipo[1]);
	}
	run_command(cur_cmdtab, t);
}
