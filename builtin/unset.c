/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:54:32 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/12 12:07:15 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	del_envlst_from_key(char *key, t_env **env_lst)
{
	t_env	*cur_tmp;
	t_env	*prv_tmp;
	t_env	*nex_tmp;

	cur_tmp = *env_lst;
	prv_tmp = NULL;
	while (cur_tmp)
	{
		nex_tmp = cur_tmp->next;
		if (is_same_str(key, cur_tmp->key))
		{
			cur_tmp->key = ft_free(cur_tmp->key);
			cur_tmp->value = ft_free(cur_tmp->value);
			if (prv_tmp == NULL)
				*env_lst = nex_tmp;
			else
				prv_tmp->next = nex_tmp;
		}
		prv_tmp = cur_tmp;
		cur_tmp = cur_tmp->next;
	}
	return ;
}

int	ft_unset(char **param, t_tok *token)
{
	int	i;

	i = 0;
	while (param[i])
		i++;
	if (i == 1)
		return (1);
	i = 1;
	while (param[i])
	{
		del_envlst_from_key(param[i], &(token->env_token));
		i++;
	}
	return (0);
}