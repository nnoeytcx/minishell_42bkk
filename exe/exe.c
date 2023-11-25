#include "../header/minishell.h"

//must set the last cmd path  when use the command !!!!!!! _=[cmd path]
unsigned int exe_command(t_tok *token)
{
    t_tok *t;
    t_cmd *t_c;
    // int i = 0;
    // int tmp_fd[2];
    int pipo[2];
    t = token;
    t_c = t->command;
    //print_env(*t);
    //printf("\n\n ----------------------------------------------");
    t->env = join_env_token(t->env_token); // malloc **char // < should do in exe loop
    // while (t->env[i])
    // {
    //     printf("\033[0;31m%s\033[0m\n", t->env[i]);
    //     i++;
    // }
    // open_and_set_io_file();
    // tmp_fd[0] = dup(STDIN_FILENO);
    // tmp_fd[1] = dup(STDOUT_FILENO);
    while (t_c != NULL)
    {
        if (t_c->next != NULL)
        {
            if (pipe(pipo) == -1)
                return(printf("PIPE FAIL \n"));
        }
        t_c->process_id = fork();
        if (t_c->process_id == -1)
            return (printf("FORK ERROR\n"));
        if (t_c->process_id == 0)
        {
            char *cmd_path = NULL;
            char **path_env;
            char **cmd_w_arg = NULL;

            cmd_w_arg = get_cmd(t_c->str_mode);
            path_env = get_envpath(t->env);
            cmd_path = get_cmdpath(t_c->str_mode->value, path_env);
            printf("cmd is [%s]\n", cmd_path);
            int i = 0;
            while (cmd_w_arg[i])
            {
                printf("[%s]->", cmd_w_arg[i]);
                i++;
            }
            printf("\n");
            if (-1 == execve(cmd_path, cmd_w_arg,t->env))
                put_errorcmd(cmd_w_arg[0], cmd_path, cmd_w_arg, errno); //<-must ues the "special exit code eiei"
        }
        t_c = t_c->next; 
    }
    t_c = t->command;
    while (t_c)
    {
        int status = 0;
        waitpid(t_c->process_id, &status,  WUNTRACED);
        // the raw data of &status is not we want so use WEXIT to convert
        t_c->process_status = WEXITSTATUS(status);
        t_c = t_c->next;
    }

    // dup2(STDOUT_FILENO, tmp_fd[1]);
    // return(wait_process());
    return (0);
}

