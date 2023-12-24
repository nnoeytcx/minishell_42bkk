#ifndef EXE_H
#define EXE_H

#include "../header/library.h"

char            **get_cmd(t_strm *str_list);
char	        *get_cmdpath(char *command, char **env);
char	        **get_envpath(char **ep);
unsigned int    exe_command(t_tok *token);
int             loop_open_file(t_strm *strm, int mode);
char	        *get_next_line(int fd);
int	            find_slash(char *str);

#endif