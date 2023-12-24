#ifndef ENV_H
#define ENV_H

#include "../header/library.h"
char 	        *get_value_from_key(char *key, t_env *token);
char	        *getenv_value(char *env_v);
char	        *getenv_key(char *env_v);
void	        print_env(t_tok token);
char            **join_env_token(t_env *env_token);

void	        if_not_define(char *env_name, char *value, t_env *env_lst);
t_env	        *new_env(char	*key, char	*value, int	mode);
t_env	        *create_env(char **env);


#endif