#include "../minishell.h"

void free_command_table(t_cmd *cmd)
{

}

void free_tok_env(t_env *env_t)
{

}

void free_env(char **ts)
{

}

void free_tok(t_tok *t)
{
    free_command_table(t->command);
    free_env_t(t->env_token);
    free_env(t->env);
}

