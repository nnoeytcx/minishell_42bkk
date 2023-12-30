#include "../header/minishell.h"

void	putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

void	err_cmd(int	*ecode, int errnum, char *cmd)
{
	if (errnum == 13 && find_slash(cmd))
	{
		putstr_fd(strerror(errnum), 2);
		*ecode = 126;
	}
	else if (find_slash(cmd))
	{
		*ecode = 127;
		putstr_fd("no such file or directory", 2);
	}
	else
	{
		*ecode = 127;
		putstr_fd("command not found", 2);
	}
}


void	errorcmd(t_cmd *t_c, char **env, int errnum)
{
	int	ecode;

	ecode = 1;
	putstr_fd("minishell: ", 2);
	err_cmd(&ecode, errnum, t_c->command_line[0]);
	putstr_fd(": ", 2);
	putstr_fd(t_c->command_line[0], 2);
	putstr_fd("\n", 2);
	if (env)
		free2d(env);
	if (t_c)
		free_cmd_tab(&t_c);
	printf("exit with ecode [%d]", ecode);
	exit(ecode);
}
