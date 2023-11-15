#include "../minishell.h"

t_strm *new_str_with_mode(char *str)
{
    if (!str)
        return (NULL);
    t_strm *new = ft_calloc(sizeof(t_strm), 1);

    new->value = str;
    new->mode = 0;
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

    // new_table->next = NULL;
    t_strm *tmp = new_table->str_mode;
    t_strm *res;
    t_strm *new;
    while (cmd_arg[i])
    {
        // write(1,"\n\nNSWM\n",7);
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
        // write(1,"PT->N\n",6);
        // write(1,"T->N\n",5);
        i++;
    }
    // write(1,"OUTT\n",5);
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