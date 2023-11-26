#include "../header/minishell.h"

t_strm *new_str_with_mode(char *str)
{
    enum type;

    if (!str)
        return (NULL);
    t_strm *new = ft_calloc(sizeof(t_strm), 1);

    new->value = ft_strdup(str);
    new->type = def;
    new->next = NULL;
    return (new);
    
}

t_cmd   *new_command_tab(char *input, t_env *env)
{
    t_cmd   *new_table;
    t_strm  *tmp;
    t_strm  *res;
    t_strm  *new;
    char    **cmd_arg;
    int     i;

    if (!input)
        return (NULL);
    new_table = ft_calloc(sizeof(t_cmd) , 1);
    cmd_arg = ft_split_sp(input, ' ');
    i = 0;
    tmp = new_table->str_mode;
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
    printf("out of set\n");
    expand_from_env(res, env);
    printf("out of expan\n");
    if (cmd_arg)
        free2d(cmd_arg);
    printf("out of free");
    new_table->fd_in = STDIN_FILENO;
    new_table->fd_out = STDOUT_FILENO;
    new_table->str_mode = res;
    return(new_table);
}

int mock_up(t_tok *token, char *input)
{
    char    **split_cmd;
    int     i;
    t_cmd   *res;
    t_cmd   *new;

    printf (">>>>>>>>>>>>>>>>> input is [%s] <<<<<<<<<<<<<<<<<<<\n", input);
    split_cmd = ft_split_sp(input, '|');
    if (split_cmd == NULL)
        return (1);
    i = 0;
    while (split_cmd[i])
    {
        printf (" | split [%d] = [%s]  |\n", i , split_cmd[i]);
        i++;
    }
    i = 0;
    res = token->command;
    while (split_cmd[i])
    {
        if (i == 0)
        {
            new = new_command_tab(split_cmd[i],token->env_token);
            (*token).command = new;
            res = new;
        }
        else
        {
            new = new_command_tab(split_cmd[i],token->env_token);
            (*token).command->next = new;
            (*token).command = (*token).command->next;
        }
        i++;
    }
    (*token).command = res;
    free2d(split_cmd);
    return (0);
}
