#include "../header/minishell.h"

void free_strm(t_strm *strm)
{
    t_strm *tmp;

    tmp = strm;
    while (strm)
    {
        tmp = strm->next;
        free(strm);
        // strm = NULL;
        strm = tmp;
    }
}

void free_command_table(t_cmd *cmd)
{
    t_cmd   *tmp;

    while (cmd)
    {
        tmp = cmd->next;
        free_strm(cmd->str_mode);
        // cmd->str_mode = NULL;
        free(cmd);
        // cmd = NULL;
        cmd = cmd->next;
    }
}

// void free_tok_env(t_env *env_t)
// {

// }

// void free_env(char **ts)
// {

// }

void free_tok(t_tok *t)
{
    free_command_table(t->command);
    t->command = NULL;
    // free_env_t(t->env_token);
    t->env_token = NULL;
    // free_env(t->env);
    t->env = NULL;
}
