#include "../minishell.h"

int parser_error(char *str)
{
    if (!str)
    {
        ft_putstr_fd(SYNTAX_ERR, 2);
        ft_putstr_fd("newline'\n", 2);
    }
    else
    {
        ft_putstr_fd(SYNTAX_ERR, 2);
        ft_putstr_fd(str, 2);
        ft_putstr_fd("'\n", 2);
    }
    return (-1);
}