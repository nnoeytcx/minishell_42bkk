#include "../header/minishell.h"

int is_sp_symbol(char *str)
{
    int len;

    if (!str)
        return (0);
    len = ft_strlen(str);
    if (0 == ft_strncmp(">", str, len))
        return (1);
    else if (0 == ft_strncmp("<", str, len))
        return (1);
    else if (0 == ft_strncmp("<<", str, len))
        return (1);
    return (0);
}

int set_mode(t_strm *str)
{
    t_strm *stm;
    int len;

    if (!str)
        return (-1);
    stm = str;
    while (stm)
    {
        len = ft_strlen(stm->value);
        if (stm->mode == DEF_VAL)
        {
            if (0 == ft_strncmp(">", stm->value, len))
            {
                stm->mode = REDIR_OUT;
                if (stm->next && !is_sp_symbol(stm->next->value))
                {
                    stm->next->mode = FILE_OUT;
                }
                else
                {
                    if (str->next)
                        parser_error(str->next->value);
                    else
                        parser_error(NULL);
                }
            }
            else if (0 == ft_strncmp("<", stm->value, len))
            {
                stm->mode = REDIR_IN;
                if (stm->next && !is_sp_symbol(stm->next->value))
                {
                    stm->next->mode = FILE_IN;
                }
                else
                {
                    if (str->next)
                        parser_error(str->next->value);
                    else
                        parser_error(NULL);
                }
            }
            else if (0 == ft_strncmp("<<", stm->value, len))
            {
                stm->mode = HERE_DOC;
                if (stm->next && !is_sp_symbol(stm->next->value))
                {
                    stm->next->mode = DOC_CUT;
                }
                else
                {
                    if (str->next)
                        parser_error(str->next->value);
                    else
                        parser_error(NULL);
                }
            }
            else if (0 == ft_strncmp(">>", stm->value, len))
            {
                stm->mode = FILE_OUT_APPEND_SY;
                if (stm->next && !is_sp_symbol(stm->next->value))
                {
                    stm->next->mode = FILE_OUT_APPEND;
                }
                else
                {
                    if (str->next)
                        parser_error(str->next->value);
                    else
                        parser_error(NULL);
                }
            }
            else if (0 == ft_strncmp("$", stm->value, 1))
                stm->mode = VAR_STR;
            else
                stm->mode = ARG_STR;
        }
        printf("set [%s] to [%d] mode\n", stm->value, stm->mode);
        stm = stm->next;
    }
    return (1);
}