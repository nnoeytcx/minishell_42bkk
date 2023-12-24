#ifndef FREE_H
#define FREE_H

#include "../header/library.h"

void	        free2d(char	**ptr);
void            free_token(t_tok *token);
int             free_cmd_tab(t_cmd **cmd_tab);
int             free_env_list(t_env **env_lst);
int             free_str_mode(t_strm **str_mode);
#endif