#ifndef MINISHELL_H
#define MINISHELL_H

#include "./library.h"


// env_handle

char 			*get_pid();
void	        put_errorcmd(char *str, char *cmd_p, char **cmd_a, int errnum);


#endif