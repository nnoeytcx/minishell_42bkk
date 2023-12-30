/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:06:53 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 17:31:40 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	free_str_mode(t_strm **str_mode)
{
	t_strm	*next;
	t_strm	*current;

	if (str_mode == NULL || *str_mode == NULL)
		return (printf("CANT FREE the STR_MODE\n"), 1);
	current = *str_mode;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*str_mode = NULL;
	return (0);
}

int	free_cmd_tab(t_cmd **cmd_tab)
{
	t_cmd	*next;
	t_cmd	*current;

	if (cmd_tab == NULL || *cmd_tab == NULL)
		return (printf("CAN FREE the CMD tab\n"),1);
	current = *cmd_tab;
	while (current)
	{
		next = current->next;
		free_str_mode(&current->str_mode);
		free(current);
		if (current->command_line)
			free2d(current->command_line);
		if (current->path_env)
			free2d(current->path_env);
		if (current->cmd_path)
			free(current->cmd_path);
		current = next;
	}
	*cmd_tab = NULL;
	return (0);
}

int	free_env_list(t_env **env_lst)
{
	t_env	*next;
	t_env	*current;

	if (env_lst == NULL || *env_lst == NULL)
		return (printf("CAN FREE the CMD tab\n"), 1);
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
	return (0);
}

void	free_token(t_tok *token)
{
	free_cmd_tab(&token->command);
	free_env_list(&token->env_token);
	free(token->pid);
	if (token->env)
		free2d(token->env);
	token = NULL;
}
