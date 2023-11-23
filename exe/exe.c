#include "../minishell.h"

int	str_n_compare(const char *s1, const char *s2, size_t n)
{
	while (n)
	{
		if (*s1 != *s2)
			return (0);
		if (*s1 == 0)
			return (0);
		n--;
		s1++;
		s2++;
	}
	return (1);
}

int	find_slash(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

char	**get_envpath(char **ep)
{
	if (!ep)
		return (NULL);
	while (*ep)
	{
		if (str_n_compare(*ep, "PATH=", 5))
			return (ft_split((*ep) + 5, ':'));
		ep++;
	}
	return (NULL);
}

char	*get_cmdpath(char *command, char **env)
{
	int		i;
	char	*prepath;
	char	*path_and_command;
	char	*ready_cmd;

	i = 0;
	if (!command)
		return (NULL);
	if (0 == access(command, X_OK) || env == NULL || find_slash(command))
	{
		ready_cmd = ft_substr(command, 0, ft_strlen(command));
		return (ready_cmd);
	}
	while (env[i])
	{
		prepath = ft_strjoin(env[i], "/");
		path_and_command = ft_strjoin(prepath, command);
		free(prepath);
		if (0 == access(path_and_command, X_OK))
			return (path_and_command);
		free(path_and_command);
		i++;
	}
	return (ft_substr(command, 0, ft_strlen(command)));
}

char    **get_cmd(t_strm *str_list)
{
    t_strm *tmp;
    char    **res;
    int     count;
    int     i;

    if (str_list == NULL)
        return (NULL);
    tmp = str_list;
    count = 0;
    while (tmp)
    {
        if (tmp->mode == ARG_STR)
            count++;
        tmp = tmp->next;
    }
    printf("count is [%d]\n", count);
    tmp = str_list;
    res = ft_calloc(sizeof(char *), count + 1);
    i = 0;
    while (tmp)
    {
        if (tmp->mode == ARG_STR)
        {
            res[i] = ft_substr(tmp->value, 0, ft_strlen(tmp->value));
            //printf("sub [%s] of res[%d]\n", tmp->value, i);
            i++;
        }
        tmp = tmp->next;
    }
    return (res);

}

char **join_env_token(t_env *env_token)
{
    t_env *tmp;
    int i;
    char    **res;
    char    *key_w_eq;

    if (!env_token)
        return (NULL);
    i = 0;
    tmp = env_token;
    while (tmp)
    {
        i++;
        tmp = tmp->next;
    }
    printf("no of token = [%d]", i);
    tmp = env_token;
    res = ft_calloc(sizeof(char *), i);
    i = 0;
    while (tmp)
    {
        key_w_eq = ft_strjoin(tmp->key, "=");
        res[i] = ft_strjoin(key_w_eq, tmp->value);
        i++;
        free(key_w_eq);
        tmp = tmp->next;
    }
    i = 0;
    printf("<-------- output is --------->\n");
    // while (res[i])
    // {
    //     printf("[%s]\n", res[i]);
    //     i++;
    // }
    return (res);
}

//must set the last cmd path  when use the command !!!!!!! _=[cmd path]
unsigned int exe_command(t_tok *token)
{
    t_tok *t;
    t_cmd *t_c;
    // int i = 0;
    // int tmp_fd[2];
    // int pipo[2];
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
     // if (t_c->file_in)
        // {
        //     printf
        // }
    while (t_c != NULL)
    {
       
        // if (t_c->next != NULL)
        // {
        //     if (pipe(pipo) == -1)
        //         return(printf("PIPE FAIL \n"));
        //     dup2(pipo[1], STDOUT_FILENO);
        //     dprintf(2,"DUP \n");
        //     close(pipo[0]);            
        // }
        // t->command->process_id = fork();
        // if (t->command->process_id == -1)
        //     return (print_error(FORK_ER));
        // if (t->command->prcess_id == 0)
        //     child_pipe_run();
        // else if (t->command->process_id > 0)
        //     parent_connect_and_move();
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
                exit(1); //<-must ues the "special exit code eiei"
        }
        t_c = t_c->next; 
    }
    t_c = t->command;
    while (t_c)
    {
        waitpid(t_c->process_id, &(t_c->process_status),  WUNTRACED); 
        t_c = t_c->next;
    }

    // dup2(STDOUT_FILENO, tmp_fd[1]);
    // return(wait_process());
    return (0);
}

