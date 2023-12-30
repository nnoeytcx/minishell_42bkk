/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:57:21 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 01:57:27 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*like if_not_define_function but can change the value and add the new key value*/
void	env_change_or_define(char *env_name, char *value, t_env *env_lst)
{
	t_env	*lst;

	lst = env_lst;
	while (lst->next)
	{
		if (0 == ft_strncmp(env_name, lst->key, ft_strlen(env_name)))
		{
			free(lst->value);
			lst->value = ft_strdup(value);
			return ;
		}
		lst = lst->next;
	}
	lst->next = new_env(env_name, value, O_KEYV);
	lst = lst->next;
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