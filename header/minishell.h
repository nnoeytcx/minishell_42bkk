#ifndef MINISHELL_H
#define MINISHELL_H

#include "./library.h"

// env_handle
char 	*get_value_from_key(char *key, t_env *token);
char	*getenv_value(char *env_v);
char	*getenv_key(char *env_v);
int		init_env_token(t_tok *token, char **env);
void	print_env(t_tok token);

char    **get_cmd(t_strm *str_list);
char	*get_cmdpath(char *command, char **env);
char	**get_envpath(char **ep);
int mock_up(t_tok *token, char *input);
void print_tok(t_tok t);
unsigned int exe_command(t_tok *token);
char **join_env_token(t_env *env_token);

void	put_errorcmd(char *str, char *cmd_p, char **cmd_a, int errnum);
int	find_slash(char *str);
int expand_from_env(t_strm *str_tab, t_env *env);
t_cmd   *new_command_tab(char *input, t_env *env);
int parser_error(char *str);

int set_mode(t_strm *str);
void	free2d(char	**ptr);
#endif