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

    printf("INNNNN \n");
    if (!str)
        return (-1);
    stm = str;
    printf("INNNNNooo \n");
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

t_strm *new_str_with_mode(char *str)
{
    if (!str)
        return (NULL);
    t_strm *new = ft_calloc(sizeof(t_strm), 1);

    new->value = str;
    new->mode = DEF_VAL;
    new->next = NULL;
    return (new);
    
}

t_cmd   *new_command_tab(char *input)
{
    if (!input)
        return (NULL);
    t_cmd *new_table = ft_calloc(sizeof(t_cmd) , 1);
    char **cmd_arg = ft_split(input, ' ');
    int i = 0;

    t_strm *tmp = new_table->str_mode;
    t_strm *res;
    t_strm *new;
    while (cmd_arg[i])
    {
        if (i == 0)
        {
            tmp = new_str_with_mode(cmd_arg[i]);
            res = tmp;
        }
        else
        {
            new = new_str_with_mode(cmd_arg[i]);
            tmp->next = new;
            tmp = new;
        }
        i++;
    }
    set_mode(res);
    // << -- just mock the deref var $
    new_table->fd_in = STDIN_FILENO;
    new_table->fd_out = STDOUT_FILENO;
    new_table->str_mode = res;
    return(new_table);
}

int mock_up(t_tok *token, char *input)
{
    char    **split_cmd;
    printf("\n-------------------------MOCK---------------------\n");
    printf (">>>>>>>>>>>>>>>>> input is [%s] <<<<<<<<<<<<<<<<<<<\n", input);
    split_cmd = ft_split(input, '|');
    if (split_cmd == NULL)
        return (1);
    int i = 0;
    while (split_cmd[i])
    {
        printf (" | split [%d] = [%s]  |\n", i , split_cmd[i]);
        i++;
    }
    i = 0;
    t_cmd *res = token->command;
    t_cmd *new;
    while (split_cmd[i])
    {
        if (i == 0)
        {
            new = new_command_tab(split_cmd[i]);
            (*token).command = new;
            res = new;
        }
        else
        {
            new = new_command_tab(split_cmd[i]);
            (*token).command->next = new;
            (*token).command = (*token).command->next;
        }
        // printf("----- [%d]------\n", i);
        // print_command_tab(new);
        i++;
    }
    (*token).command = res;
   //print_command_tab((token->command));
    // print_command_tab(token->command);
    return (0);
}

// int exe_command(t_tok token)
// {

// }