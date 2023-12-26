#ifndef EXE_H
#define EXE_H

#define IN_FILE 1
#define OUT_FILE 2
#define BUFFER_SIZE 1
#include "../header/library.h"

char            **get_cmd(t_strm *str_list);
char	        *get_cmdpath(char *command, char **env);
char	        **get_envpath(char **ep);
unsigned int    exe_command(t_tok *token);
int				loop_open_file(t_cmd *t, int mode);
char	        *get_next_line(int fd);
int	            find_slash(char *str);
void			loop_and_assign_heredoc(t_cmd *t);
int				str_n_compare(const char *s1, const char *s2, size_t n);
#endif