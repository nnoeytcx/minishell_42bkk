#ifndef ENV_HANDLE_H
#define ENV_HANDLE_H
#include "../minishell.h"

char 	*get_value_from_key(char *key, t_env *token);

char	*getenv_value(char *env_v);
char	*getenv_key(char *env_v);
int		init_env_token(t_tok *token, char **env);

// utill << have to add libft later ////
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
#endif