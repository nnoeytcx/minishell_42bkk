#ifndef BUILTIN_H
#define BUILTIN_H


#define GET 1
#define PRINT 2

int 	is_builtin(char *cmd);
int 	run_builtin(char **cmd_lst, t_tok *token);
int		ft_env(t_env *env_list);
int		ft_pwd(int mode, char **str);
int		ft_echo(char **param);
int		ft_cd(char **param, t_env *env_lst);
int 	ft_exit(char **param, t_tok *token);
int 	ft_export(char **param, t_tok *token);
#endif