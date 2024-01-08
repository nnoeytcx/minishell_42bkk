/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:57:21 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/08 20:49:32 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	env_change_or_define(char *env_name, char *value, t_env *env_lst)
{
	t_env	*lst;
	t_env	*prv_lst;

	lst = env_lst;
	while (lst)
	{
		prv_lst = lst;
		if (is_same_str(env_name, lst->key))
		{
			lst->value = ft_free(lst->value);
			lst->value = ft_strdup(value);
			return ;
		}
		lst = lst->next;
	}
	prv_lst->next = new_env(env_name, value, O_KEYV);
	return ;
}

void	if_not_define(char *env_name, char *value, t_env *env_lst)
{
	t_env	*lst;

	lst = env_lst;
	while (lst->next)
	{
		if (0 == ft_strncmp(env_name, lst->key, ft_strlen(env_name)))
			return ;
		lst = lst->next;
	}
	lst->next = new_env(env_name, value, O_KEYV);
	lst = lst->next;
	return ;
}
