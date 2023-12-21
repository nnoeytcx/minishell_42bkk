#include "../header/minishell.h"

void	free2d(char	**ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

int free_str_mode(t_strm **str_mode)
{
    t_strm *next;
    t_strm *current;

    if (str_mode == NULL || *str_mode == NULL)
        return (printf("CANT FREE the STR_MODE\n"),1);
    current = *str_mode;
    while (current)
    {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    *str_mode = NULL;
}

int free_cmd_tab(t_cmd **cmd_tab)
{   
    t_cmd *next;
    t_cmd *current;

    if (cmd_tab == NULL || *cmd_tab == NULL)
        return (printf("CAN FREE the CMD tab\n"),1);
    current = *cmd_tab;
    while (current)
    {
        next = current->next;
        free_str_mode(&current->str_mode);
        free(current);
        current = next;
    }
    *cmd_tab = NULL;
}

int free_env_list(t_env **env_lst)
{
    t_env *next;
    t_env *current;

    if (env_lst == NULL || *env_lst == NULL)
        return (printf("CAN FREE the CMD tab\n"),1);
    current = *env_lst;
    while (current)
    {
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }
    *env_lst = NULL;
}

void free_token(t_tok *token)
{
    free_cmd_tab(&token->command);
    free_env_list(&token->env_token);
    if (token->env)
        free(token->env);
    token = NULL;
}
