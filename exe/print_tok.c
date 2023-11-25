#include "../header/minishell.h"

void print_command_tab(t_cmd *cmd)
{
    int i = 0;
    int k = 0;
    t_cmd *tmp = cmd;
    t_strm *stt;
    while (tmp != NULL)
    {
        // printf("pipe[%d][%d]\n", cmd->pipo[0], cmd->pipo[1]);
        // printf("fd in [%d] fd out [%d]\n", cmd->fd_in,cmd->fd_out);
        // printf("f_in [%s], f_out [%s]\n", cmd->file_in,cmd->file_out);
        stt = tmp->str_mode;
        printf("\n -----  {%d} cmd is [%p] -------\n",k, cmd);
        i = 0;
        while (stt)
        {
           // printf(" | strm [%d] ", i);
            printf("value [%s] mode [%d] -> ",stt->value, stt->mode);
            stt = stt->next;
            i++;       
        }
        k++;
        tmp = tmp->next;
    }
    printf ("\n\n");

}


void print_tok(t_tok t)
{
    printf("\n---------------token-----------\n");
    printf("--------vvvvvvv command tab---------\n");
    print_command_tab((t.command));;
}