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
        dprintf(2, "[%s]BEFORE : in connect mom [%d] \n", t_c->str_mode->value,t_c->next->fd_in);
        t_c->next->fd_in = dup(pipe[0]);
        dprintf(2, "[%s]AFTER : connect [%s]the fd [%d]\n", t_c->str_mode->value,t_c->next->str_mode->value, t_c->next->fd_in);
        close(pipe[0]);
    }
}

void run_command(t_cmd *t_c, char **env)
{
    char    **cmd_arg;
    char    *cmd_w_path;
    char    **path_env;

    cmd_arg = NULL;
    cmd_w_path = NULL;
    cmd_arg = get_cmd(t_c->str_mode); // get the string join together
    path_env = get_envpath(env); // need to get the path every time cus you can set the new thong to this
    cmd_w_path = get_cmdpath(cmd_arg[0], path_env); // search for the avalable path and combine with the string 0
    dprintf(2,"[%s]before : exe [%s]\nfd_in [%d]\nfd_out [%d]\n", t_c->str_mode->value,cmd_w_path,t_c->fd_in,t_c->fd_out);
    if (t_c->fd_in != STDIN_FILENO)
    {
        dprintf(2, "[%s]dup in [%d] to [%d]\n",t_c->str_mode->value ,t_c->fd_in, 0);
        dup2(t_c->fd_in, 0);
        close(t_c->fd_in);
    }
    if (t_c->fd_out != STDOUT_FILENO)
    {
        dprintf(2, "[%s]dup out [%d] to [%d]\n", t_c->str_mode->value,t_c->fd_out, 1);
        dup2(t_c->fd_out, 1);
        close(t_c->fd_out);
    }
    if (-1 == execve(cmd_w_path, cmd_arg, env))
    {
        perror("ERROR");
        put_errorcmd(cmd_arg[0], cmd_w_path, cmd_arg, errno);
    }
    exit(1);

}
void    child_pipe_and_run(t_cmd *t_c, char **env, int pipe[2])
{
    dprintf(2, "[%s]BF loop open : in [%d] out [%d]\n",t_c->str_mode->value, t_c->fd_in, t_c->fd_out);
    t_c->fd_in = loop_open_file(t_c, IN_FILE);
    t_c->fd_out = loop_open_file(t_c, OUT_FILE);
    dprintf(2, "[%s]AF loop open : in [%d] out [%d]\n", t_c->str_mode->value,t_c->fd_in, t_c->fd_out);
    
    if (t_c->next != NULL)
    {
        dprintf(2, "[%s]have next cmd dup [%d] to [%d]\n",t_c->str_mode->value, pipe[1], 1);
        dup2(pipe[1], 1);
        close(pipe[1]);
    }
    run_command(t_c, env);
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
        dprintf(2, "[%s]\n", t_c->str_mode->value);
        if (t_c->next != NULL)
        {
            dprintf(2, "[%s]have next cmd [%s]\n", t_c->str_mode->value,t_c->next->str_mode->value);
            if (pipe(pipo) == -1)
                return(printf("PIPE FAIL \n"));
            dprintf(2, "[%s]create : pipe[0] = [%d] pipe[1] = [%d]\n\n",t_c->str_mode->value, pipo[0], pipo[1]);
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

