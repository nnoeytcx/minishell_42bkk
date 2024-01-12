/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:02:35 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/11 11:09:08 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	setsig_exe(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 0)
	{
		signal(SIGINT, &signal_hunter);
		signal(SIGQUIT, &signal_hunter);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	run_command(t_cmd *t_c, t_tok *t)
{
	if (is_builtin(t_c->command_line[0]))
		return (exit(run_builtin(t_c->command_line, t)));
	t_c->path_env = get_envpath(t->env);
	t_c->cmd_path = get_cmdpath(t_c->command_line[0], t_c->path_env);
	if (loop_open_file(t_c))
		execve(t_c->cmd_path, t_c->command_line, t->env);
	close(0);
	close(1);
	errorcmd(t_c, t, errno);
	close(2);
	exit(1);
}

int	fork_and_execve(t_tok *t)
{
	t_cmd	*t_c;
	int		pipo[2];
	int		tmp_fd;

	tmp_fd = dup(STDIN_FILENO);
	t_c = t->command;
	setsig_exe(1);
	while (t_c)
	{
		t_c->command_line = get_cmd(t_c->str_mode);
		if (t_c->next != NULL)
			if (pipe(pipo) == -1)
				return (perror("PIPE : "), errno);
		t_c->process_id = fork();
		if (t_c->process_id == -1)
			return (perror("FORK : "), errno);
		if (t_c->process_id == 0)
			child_process_run(t, t_c, pipo, tmp_fd);
		if (t_c->process_id > 0)
			parent_prepare_next_command(t_c, pipo, &tmp_fd);
		t_c = t_c->next;
	}
	close(tmp_fd);
	t->env = free2d(t->env);
	return (wait_all_child(t->command));
}

int	execute_command(t_tok *token)
{
	t_tok	*t;
	t_cmd	*t_c;

	t = token;
	t_c = t->command;
	if (!loop_and_assign_heredoc(t_c))
		return (0);
	t->command_count = count_command_tab(t_c);
	t->env = join_env_token(t->env_token);
	if (t->command_count == 1 && command_is_builtin(t_c))
		return (run_single_builtin(t));
	return (fork_and_execve(t));
}
