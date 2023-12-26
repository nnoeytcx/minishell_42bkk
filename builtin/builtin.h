#ifndef BUILTIN_H
#define BUILTIN_H


#define GET 1
#define PRINT 2

int		ft_env(t_env *env_list);
int		ft_pwd(int mode, char **str);

#endif