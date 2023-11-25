#include "../minishell.h"

int expand_from_env(t_strm *str_tab, t_env *env)
{
    t_strm *s;
    t_env  *e;
    char    *env_str;

    e = env;
    s = str_tab;
    while (s)
    {
        if (s->mode == VAR_STR && !ft_strncmp(s->value, "$", 1))
        {
            env_str = get_value_from_key((s->value + 1), e);
            free (s->value);
            s->value = env_str;
            s->mode = ARG_STR;
        }
        s = s->next;
    }
    return (0);
}