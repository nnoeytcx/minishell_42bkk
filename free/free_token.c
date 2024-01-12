/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:06:53 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/12 23:50:09 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
	}
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
	token->command = free_cmd_tab(token->command);
	token->env_token = free_env_list(token->env_token);
	if (token->env)
		token->env = free2d(token->env);
	if (token->cur_input)
		token->cur_input = ft_free(token->cur_input);
	if (token->home_dir)
		token->home_dir = ft_free(token->home_dir);
	if (token->pwd)
		token->pwd = ft_free(token->pwd);
	clear_history();
	close(0);
	close(1);
	close(2);
	return (NULL);
}
