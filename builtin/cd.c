#include "../header/minishell.h"

int ft_cd(char **param, t_env *env_lst)
{
    char    *cwd;
    char    *old_pwd;
    char    *new_pwd;
    int     i;

    i = 0;
    while (param[i])
        i++;
    if (i > 2)
    {
        dprintf(2, "minishell: cd: too many arguments\n");
        return (1);
    }
    old_pwd = getcwd(NULL,0);
    if (i == 1)
    {
        if (-1 == chdir("~"))
        {
            perror("minishell: cd: ");
            return (1);
        }
    }
    else if (-1 == chdir(param[1]))
    {
        perror("minishell: cd: ");
        return (1);
    }
    new_pwd = getcwd(NULL, 0);
    dprintf(2, "PWD : old [%s] new [%s]\n", old_pwd, new_pwd);
    if_not_define("OLDPWD", old_pwd, env_lst);
    if_not_define("PWD", new_pwd, env_lst);
    free(new_pwd);
    free(old_pwd);
    return (0);
}
