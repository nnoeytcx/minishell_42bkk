#include "../header/minishell.h"

char **join_env_token(t_env *env_token)
{
    t_env *tmp;
    int i;
    char    **res;
    char    *key_w_eq;

    if (!env_token)
        return (NULL);
    i = 0;
    tmp = env_token;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    tmp = env_token;
    res = ft_calloc(sizeof(char *), i+1); // fix the oeve flow by +1
    i = 0;
    while (tmp)
    {
        key_w_eq = ft_strjoin(tmp->key, "=");
        res[i] = ft_strjoin(key_w_eq, tmp->value);
        i++;
        free(key_w_eq);
        tmp = tmp->next;
    }
    res[i] = NULL;
    return (res);
}

