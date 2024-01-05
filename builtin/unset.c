/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:54:32 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/05 18:14:11 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	del_envlst_from_key(char *key, t_env *env_lst)
{
	t_env	*tmp;
	t_env	*prv_tmp;
	t_env	*nex_tmp;

	while (tmp)
	{
		prv_tmp = tmp;
		nex_tmp = tmp->next;
		if (is_same_str(key, tmp->key))
		{
		}
		tmp = tmp->next;
	}
	return ;
}

int	ft_unset(char **param, t_tok *token)
{
	int	i;

	i = 0;
	dprintf(2, "IN unset!!!!\n");
	while (param[i])
		i++;
	if (i == 1)
		return (1);
	i = 1;
	while (param[i])
	{
		del_envlst_from_key(param[i], token->env_token);
		i++;
	}
	return (0);
}