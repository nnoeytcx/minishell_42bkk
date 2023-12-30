/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:47:51 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 13:17:42 by pruenrua         ###   ########.fr       */
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
		dprintf(2,"waiting for [%s][%d]\n",cmd_tab_t->str_mode->value, cmd_tab_t->process_id);
		waitpid(cmd_tab_t->process_id, &status,  WUNTRACED);
		cmd_tab_t->process_status = WEXITSTATUS(status);
		dprintf(2,"\nwaiting for [%s][%d] finish return [%d]\n",cmd_tab_t->str_mode->value, cmd_tab_t->process_id, cmd_tab_t->process_status);
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
	dprintf(2,"[%s]before : exe [%s]\nfd_in [%d]\nfd_out [%d]\n", t_c->str_mode->value,t_c->cmd_path,t_c->fd_in,t_c->fd_out);
	if (t_c->fd_in != STDIN_FILENO)
	{
		dprintf(2, "[%s]dup in [%d] to [%d]\n",t_c->str_mode->value ,t_c->fd_in, 0);
		dup2(t_c->fd_in, 0);
		close(t_c->fd_in);
	}
	if (t_c->fd_out != STDOUT_FILENO)
	{
		dprintf(2, "[%s]dup out [%d] to [%d]\n", t_c->str_mode->value,t_c->fd_out, 1);
		dup2(t_c->fd_out, 1);
		close(t_c->fd_out);
	}
	dprintf(2, "\033[0;97m---- output -----\n\n");
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

//must set the last cmd path  when use the command !!!!!!! _=[cmd path]
unsigned int	exe_command(t_tok *token)
{
	t_tok	*t;
	t_cmd	*t_c;
	int		pipo[2];

	t = token;
	t_c = t->command;
	dprintf(2, "before join\n");
	t->env = join_env_token(t->env_token);
	dprintf(2, "afte join\n");
	loop_and_assign_heredoc(t_c);
	dprintf(2,"pid in parent id -> %d\n", getpid());
	while (t_c != NULL)
	{
		t_c->command_line = get_cmd(t_c->str_mode);
		dprintf(2, "[%s]\n", t_c->str_mode->value);
		if (t_c->next != NULL)
		{
			dprintf(2, "[%s] have next cmd [%s]\n", t_c->str_mode->value,t_c->next->str_mode->value);
			if (pipe(pipo) == -1)
				return (printf("PIPE FAIL \n"));
			dprintf(2, "[%s] create : pipe[0] = [%d] pipe[1] = [%d]\n\n",t_c->str_mode->value, pipo[0], pipo[1]);
		}
		if (is_builtin(t_c->command_line[0]) && t_c->next == NULL)
		{
			dprintf(2, "[%s] is _built in\n",t_c->command_line[0]);
			return (run_builtin(t_c->command_line, t));
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

