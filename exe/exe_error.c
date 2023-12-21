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


void	put_errorcmd(char *str, char *cmd_p, char **cmd_a, int errnum)
{
	int	ecode;

	ecode = 1;
	putstr_fd("pipex42: ", 2);
	err_cmd(&ecode, errnum, str);
	putstr_fd(": ", 2);
	putstr_fd(str, 2);
	putstr_fd("\n", 2);
	if (cmd_p)
		free(cmd_p);
	free2d(cmd_a);
	printf("exit with ecode [%d]", ecode);
	exit(ecode);
}
