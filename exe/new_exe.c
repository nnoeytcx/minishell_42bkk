// valgrind --tool=memcheck --tool=callgrind --num-callers=20 --track-fds=yes --error-exitcode=1
#include "../header/minishell.h"

int ft_close(int fd)
{
	if (fd == -1)
		return (-1);
	dprintf(2, "pid -> [%d] close [%d]\n",getpid(), fd);
	close(fd);
	return (-1);
}

int		count_command_tab(t_cmd *cmd)
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

void	run_command(t_cmd *t_c, t_tok *t)
{
	t_c->path_env = get_envpath(t->env);
	t_c->cmd_path = get_cmdpath(t_c->command_line[0], t_c->path_env);
	if (loop_open_file(t_c))
	{
		ft_putstr_fd("\n-------------------- output ----------------\n", 2);
		execve(t_c->cmd_path, t_c->command_line, t->env);
	}
	perror("ERROR: ");
	close(0);
	close(1);
	close(2);
	errorcmd(t_c, t, errno);
	exit(1);
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
		waitpid(cmd_tab_t->process_id, &exit_status,  WUNTRACED);
		dprintf(2, "the exit status %d\n", exit_status);
		if (WIFSIGNALED(exit_status))
		{
			if (exit_status == 3)
			{
				dprintf(2, "QUIT : %d\n", exit_status);
				exit_status = 131;
			}
			else
				exit_status = 130;
		}
		else
			exit_status = WEXITSTATUS(exit_status);
		if (cmd_tab_t->process_status == -1)
			cmd_tab_t->process_status = exit_status;
		cmd_tab_t = cmd_tab_t->next;
	}
	return (exit_status);
}

void child_process_run(t_tok *t, t_cmd *cur_cmdtab, int pipo[2], int fd_in)
{
	term_setup(CHILD_PROCESS);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	ft_putstr_fd("in command \n",2);
	int i = -1;
	while (cur_cmdtab->command_line[++i])
	{
		ft_putstr_fd(" [ ",2);
		ft_putstr_fd(cur_cmdtab->command_line[i], 2);
		ft_putstr_fd(" ]->",2);
	}
	ft_putstr_fd("\n", 2);
	//////// can check the bulit in in the child to check leaks

	if (cur_cmdtab->next)
	{
		close(pipo[0]);
		dup2(pipo[1], STDOUT_FILENO);
		close(pipo[1]);
	}
	run_command(cur_cmdtab, t);
}

unsigned int	fork_and_execve(t_tok *t)
{
	t_cmd 	*t_c;
	int		pipo[2];
	int		tmp_fd;

	tmp_fd = dup(STDIN_FILENO);
	t_c = t->command;
	while (t_c)
	{
		t_c->command_line = get_cmd(t_c->str_mode);
		if (t_c->next != NULL)
		{
			if (pipe(pipo) == -1)
				return (perror("PIPE : "), errno);
		}
		t_c->process_id = fork();
		if (t_c->process_id == -1)
			return (perror("FORK : "), errno);
		if (t_c->process_id == 0)
			child_process_run(t, t_c, pipo, tmp_fd);
		if (t_c->process_id > 0)
			parent_prepare_next_command(t_c, pipo, &tmp_fd);
		usleep(1);
		t_c = t_c->next;
	}
	t_c = t->command;
	close(tmp_fd);
	t->env = free2d(t->env);
	return (wait_all_child(t_c));
}

unsigned int execute_command(t_tok *token)
{
	t_tok 	*t;
	t_cmd 	*t_c;

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