//#include "minishell.h"

#include <stdlib.h>
#include <stdio.h>

char	**ft_split(char *s);

/*void    ft_getfdin(char *input)
{
    //ex : "cat minishell.c | wc -l > outfile"

}
void    ft_getfdout(char *input);
void    ft_getcommand(char *input);*/

typedef struct s_amd
{
	int redirect; // <----- redirect flag bool 0 is default if have redirect chage to 1
	int pipo[2];	// <--- for pipe init to [0,0]
	int fd_in;	// <------ default is 0 set by open after if have file_in;
	char *file_in; // <--- the file name that user pass in command (command < eiei.txt) want "eiei.txt"
	char **command;	// <-- the split command {"ls" , "-la", "......"}
	char *file_out; // <-- file out str for output (command > eiei.txt) want eiei.txt
	int fd_out;	// default 1 <set by open if have file_out
	struct	s_amd *next;
}	t_cmd ;

t_cmd *ft_initcmd (t_cmd *cmd, char **input, int i, int j)
{
    cmd->redirect = 0;
    cmd->pipo[0] = 0;
    cmd->pipo[1] = 0;
    cmd->fd_in = 0;
    cmd->fd_out = 1;
    cmd->next = NULL; 
    //cmd->file_in = ft_getfdin(input);
    //cmd->file_out = ft_getfdout(input);
    //cmd->command = ft_getcommand(input);
    return (cmd);
}

void    ft_creatnode (t_cmd *cmd, char **input, int len)
{
    int i = 0;
    int j = 0;

    while (i < len)
    {
        if (input[i][0] == '|')
        {
            //creat new node use input from j to i
            //set old_node->next = &(new_node)

            //cmd = ft_initcmd (cmd, input, i, j);

            printf(" (%d) to (%d)\n", j, i - 1);
            j = i + 1;
        }
        else
            printf("[%s] ", input[i]);
        i++;
    }
    printf(" (%d) to (%d)\n", j, i - 1);
}

int main(int argc, char *argv[]) 
{
    t_cmd   *cmd;

    int i = 0;
    char **res;

    res = ft_split(argv[1]);
    while (res[i])
    {
        //printf("[%s] ", res[i]);
        i++; 
    }
    //printf("---%d---", i);
    ft_creatnode (cmd, res, i);
    
}