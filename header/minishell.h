#ifndef MINISHELL_H
#define MINISHELL_H

#include "./library.h"

t_strm      	*new_str_with_mode(char *str);
int         	in_value_split(t_strm *str);
int	            is_redirect(char c);
char const	    *count_for_redirect(char const *s);
char	        get_quote_trigger(char quote_trigger, char const *s);
// env_handle
char 	        *get_value_from_key(char *key, t_env *token);
char	        *getenv_value(char *env_v);
char	        *getenv_key(char *env_v);
// int		init_env_token(t_tok *token, char **env);
void	        print_env(t_tok token);

char            **get_cmd(t_strm *str_list);
char	        *get_cmdpath(char *command, char **env);
char	        **get_envpath(char **ep);
int             lexer_parser(t_tok *token, char *input);
void            print_tok(t_tok t);
unsigned int    exe_command(t_tok *token);
char            **join_env_token(t_env *env_token);

void	        put_errorcmd(char *str, char *cmd_p, char **cmd_a, int errnum);
int	            find_slash(char *str);
int             expand_from_env(t_strm *str_tab, t_env *env);
t_cmd           *new_command_tab(char *input, t_env *env);
int             parser_error(char *str);

int             set_mode(t_strm *str);
char	        **ft_split_sp(char const *s, char c);
char	        **ft_split_pipe(char const *s, char c);
void	        free2d(char	**ptr);
void            free_token(t_tok *token);
int             free_cmd_tab(t_cmd **cmd_tab);
int             free_env_list(t_env **env_lst);
int             free_str_mode(t_strm **str_mode);
void	        if_not_define(char *env_name, char *value, t_env *env_lst);
t_env	        *new_env(char	*key, char	*value, int	mode);
t_env	        *create_env(char **env);
int             loop_open_file(t_strm *strm, int mode);
char	        *get_next_line(int fd);
#endif