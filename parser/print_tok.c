#include "../minishell.h"

void print_command_tab(t_cmd *cmd)
{
    int i = 0;
    int k = 0;
    t_cmd *tmp = cmd;
    t_strm *stt;
    while (tmp != NULL)
    {
        stt = tmp->str_mode;
        printf("\n -----  {%d} cmd is [%p] -------\n",k, cmd);
        i = 0;
        while (stt)
        {
            printf("value [%s] mode [%d] -> ",stt->value, stt->mode);
            stt = stt->next;
            i++;       
        }
        printf("\nprocess id[%d]\n status[%d]\n", tmp->process_id, tmp->process_status);
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