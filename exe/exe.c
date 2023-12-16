#include "../header/minishell.h"

int    wait_all_child(t_cmd *cmd_tab)
{
    t_cmd   *cmd_tab_t;
    int     status;

    status = 1;
    cmd_tab_t = cmd_tab;
    while (cmd_tab_t)
    {
        waitpid(cmd_tab_t->process_id, &status,  WUNTRACED);
        cmd_tab_t->process_status = WEXITSTATUS(status);
        cmd_tab_t = cmd_tab_t->next;
    }
    return (WEXITSTATUS(status));
}

void    mom_connect_pipe(t_cmd *t_c, int pipe[2])
{
    if (t_c->next != NULL)
    {
        close(pipe[1]);
        t_c->next->fd_in = dup(pipe[0]);
        close(pipe[0]);
    }
}

void    child_pipe_and_run(t_cmd *t_c, char **env, int pipe[2])
{
    char *cmd_path = NULL;
    char **path_env;
    char **cmd_w_arg = NULL;

    if (t_c->next != NULL)
    {
        dup2(pipe[1], 1);
        close(pipe[1]);
    }
    if (t_c->fd_in != STDOUT_FILENO)
        dup2(t_c->fd_in, 0);
    cmd_w_arg = get_cmd(t_c->str_mode);
    path_env = get_envpath(env);
    cmd_path = get_cmdpath(t_c->str_mode->value, path_env);
    if (-1 == execve(cmd_path, cmd_w_arg, env))
    {
        perror("ERROR");
        put_errorcmd(cmd_w_arg[0], cmd_path, cmd_w_arg, errno);
    }
}

//must set the last cmd path  when use the command !!!!!!! _=[cmd path]
unsigned int exe_command(t_tok *token)
{
    t_tok *t;
    t_cmd *t_c;
    int pipo[2];
    t = token;
    t_c = t->command;
    t->env = join_env_token(t->env_token); // malloc **char // < should do in exe loop
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
            child_pipe_and_run(t_c, t->env, pipo);
        if (t_c->process_id > 0)
            mom_connect_pipe(t_c, pipo);
        t_c = t_c->next;
    }
    t_c = t->command;
    return (wait_all_child(t_c));
}

