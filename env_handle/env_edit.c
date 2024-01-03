/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:57:21 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/03 10:20:38 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*like if_not_define_function but can change the value and add the new key value*/
void	env_change_or_define(char *env_name, char *value, t_env *env_lst)
{
	t_env	*lst;
	t_env	*prv_lst;

	lst = env_lst;
	dprintf(2, "change or define %s\n", env_name);
	while (lst)
	{
		prv_lst = lst;
		if (is_same_str(env_name, lst->key))
		{
			dprintf(2, "adjust %s\n", env_name);
			free(lst->value);
			lst->value = ft_strdup(value);
			return ;
		}
		lst = lst->next;
	}
	dprintf(2, "set new %s \n", env_name);
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