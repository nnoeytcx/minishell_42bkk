#include "../minishell.h"

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
    //printf("no of token = [%d]", i);
    tmp = env_token;
    res = ft_calloc(sizeof(char *), i);
    i = 0;
    while (tmp)
    {
        key_w_eq = ft_strjoin(tmp->key, "=");
        res[i] = ft_strjoin(key_w_eq, tmp->value);
        i++;
        free(key_w_eq);
        tmp = tmp->next;
    }
    // i = 0;
    // printf("<-------- output is --------->\n");
    // while (res[i])
    // {
    //     printf("[%s]\n", res[i]);
    //     i++;
    // }
    return (res);
}