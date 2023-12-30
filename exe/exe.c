/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:47:51 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 14:48:40 by pruenrua         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */


#include "../header/minishell.h"

char	*get_pid(void)
{
	int		fd;
	char	*input;
	char	*pid;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd < 0)
		return (ft_strdup("Process id not found"));
	while (1)
	{
		input = get_next_line(fd);
		if (str_n_compare("Pid", input, 3) || input == NULL)
			break;
		free(input);
	}
	pid = ft_strrchr(input, '\t');
	pid = ft_strdup(pid);
	free(input);
	close(fd);
	return (pid);
}

int	wait_all_child(t_cmd *cmd_tab)
{
	t_cmd	*cmd_tab_t;
	int		status;

	status = 1;
	cmd_tab_t = cmd_tab;
	while (cmd_tab_t)
	{
		waitpid(cmd_tab_t->process_id, &status,  WUNTRACED);
		if (cmd_tab_t->process_status == -1)
			cmd_tab_t->process_status = WEXITSTATUS(status);
		cmd_tab_t = cmd_tab_t->next;
	}
	return (WEXITSTATUS(status));
}

void	mom_connect_pipe(t_cmd *t_c, int pipe[2])
{
	dprintf(2,"parent after fork id getpid = [%d] -> %d\n",getpid(), t_c->process_id);
	if (t_c->next != NULL)
	{
	    close(pipe[1]);
	    dprintf(2, "[%s]BEFORE : in connect mom [%d] \n", t_c->str_mode->value,t_c->next->fd_in);
	    t_c->next->fd_in = dup(pipe[0]);
	    dprintf(2, "[%s]AFTER : connect [%s]the fd [%d]\n", t_c->str_mode->value,t_c->next->str_mode->value, t_c->next->fd_in);
	    close(pipe[0]);
	}
}

void	run_command(t_cmd *t_c, char **env)
{
	t_c->path_env = get_envpath(env);
	t_c->cmd_path = get_cmdpath(t_c->command_line[0], t_c->path_env);
	if (t_c->fd_in != STDIN_FILENO)
	{
		dup2(t_c->fd_in, 0);
		close(t_c->fd_in);
	}
	if (t_c->fd_out != STDOUT_FILENO)
	{
		dup2(t_c->fd_out, 1);
		close(t_c->fd_out);
	}
	if (-1 == execve(t_c->cmd_path, t_c->command_line, env))
	{
		perror("ERROR: ");
		errorcmd(t_c, env, errno);
	}
	exit(1);
}

void	child_pipe_and_run(t_cmd *t_c, char **env, int pipe[2])
{
	dprintf(2,"pid in chile id -> %d\n", getpid());
	dprintf(2, "[%d][%s] BF loop open : in [%d] out [%d]\n",t_c->process_id,t_c->str_mode->value, t_c->fd_in, t_c->fd_out);
	t_c->fd_in = loop_open_file(t_c, IN_FILE);
	t_c->fd_out = loop_open_file(t_c, OUT_FILE);
	dprintf(2, "[%d][%s] AF loop open : in [%d] out [%d]\n",t_c->process_id, t_c->str_mode->value,t_c->fd_in, t_c->fd_out);

	if (t_c->next != NULL)
	{
		dprintf(2, "[%d][%s] have next cmd dup [%d] to [%d]\n",t_c->process_id,t_c->str_mode->value, pipe[1], 1);
		dup2(pipe[1], 1);
		close(pipe[1]);
	}
	run_command(t_c, env);
}

unsigned int	exe_command(t_tok *token)
{
	t_tok	*t;
	t_cmd	*t_c;
	int		pipo[2];

	t = token;
	t_c = t->command;
	t->env = join_env_token(t->env_token);
	loop_and_assign_heredoc(t_c);
	if (t_c->next == NULL)
	{
		t_c->command_line = get_cmd(t_c->str_mode);
		if (is_builtin(t_c->command_line[0]))
		{
			t_c->process_status = run_builtin(t_c->command_line, t);
			free2d(t_c->command_line);
			t_c->command_line = NULL;
			free2d(t->env);
			t->env = NULL;
			return (t_c->process_status);
		}
		free2d(t_c->command_line);
	}
	while (t_c != NULL)
	{
		t_c->command_line = get_cmd(t_c->str_mode);
		dprintf(2, "[%s]\n", t_c->str_mode->value);
		if (t_c->next != NULL)
		{
			if (pipe(pipo) == -1)
				return (printf("PIPE FAIL \n"));
		}
		else
		{
			t_c->process_id = fork();
			if (t_c->process_id == -1)
				return (printf("FORK ERROR\n"));
			if (t_c->process_id == 0)
				child_pipe_and_run(t_c, t->env, pipo);
			if (t_c->process_id > 0)
				mom_connect_pipe(t_c, pipo);
		}
		t_c = t_c->next;
	}
	t_c = t->command;
	free2d(t->env);
	return (wait_all_child(t_c));
}

