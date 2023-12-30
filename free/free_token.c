/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:06:53 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 15:25:14 by pruenrua         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

char	**free2d(char	**ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (NULL);
	while (ptr[i])
	{
		ptr[i] = ft_free(ptr[i]);
		i++;
	}
	ptr = ft_free(ptr);
	return (NULL);
}

t_strm	*free_str_mode(t_strm *str_mode)
{
	t_strm	*next;
	t_strm	*current;

	if (str_mode == NULL || str_mode == NULL)
		return (printf("CANT FREE the STR_MODE\n"), NULL);
	current = str_mode;
	while (current)
	{
		next = current->next;
		if (current->value)
			current->value = ft_free(current->value);
		current = ft_free(current);
		current = next;
	}
	return (NULL);
}

t_cmd	*free_cmd_tab(t_cmd *cmd_tab)
{
	t_cmd	*next;
	t_cmd	*current;

	if (cmd_tab == NULL || cmd_tab == NULL)
		return (printf("CAN FREE the CMD tab\n"),NULL);
	current = cmd_tab;
	int i = 0;
	dprintf(2, "free CMD_TAB\n");
	while (current)
	{
		next = current->next;
		current->str_mode = free_str_mode(current->str_mode);
		if (current->command_line)
			current->command_line = free2d(current->command_line);
		if (current->path_env)
			current->path_env = free2d(current->path_env);
		if (current->cmd_path)
			current->cmd_path = ft_free(current->cmd_path);
		current = ft_free(current);
		current = next;
		i++;
	}
	dprintf(2, "free [%d]\n", i);
	return (NULL);
}

t_env	*free_env_list(t_env *env_lst)
{
	t_env	*next;
	t_env	*current;

	if (env_lst == NULL || env_lst == NULL)
		return (printf("CAN FREE the CMD tab\n"), NULL);
	current = env_lst;
	while (current)
	{
		next = current->next;
		current->key = ft_free(current->key);
		current->value = ft_free(current->value);
		current = ft_free(current);
		current = next;
	}
	return (0);
}

t_tok	*free_token(t_tok *token)
{
	dprintf(2, "IN FREE \n");
	token->command = free_cmd_tab(token->command);
	dprintf(2, "FREE CMD\n");
	token->env_token = free_env_list(token->env_token);
	dprintf(2, "FREE ENV\n");
	if (token->env)
		token->env = free2d(token->env);
	dprintf(2, "FREE ENVVV\n");
	clear_history();
	dprintf(2, "cler history\n");
	return (NULL);
}
