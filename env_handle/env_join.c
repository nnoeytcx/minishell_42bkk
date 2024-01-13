/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:05:35 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/13 13:50:22 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	count_env(t_env *env_lst)
{
	t_env	*tmp;
	int		ret;

	ret = 0;
	tmp = env_lst;
	while (tmp)
	{
		ret++;
		tmp = tmp->next;
	}
	return (ret);
}

char	**join_env_token(t_env *env_token)
{
	t_env		*tmp;
	char		**res;
	char		*key_w_eq;
	int			i;

	if (!env_token)
		return (NULL);
	i = count_env(env_token);
	tmp = env_token;
	res = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (tmp)
	{
		key_w_eq = ft_strjoin(tmp->key, "=");
		res[i] = ft_strjoin(key_w_eq, tmp->value);
		i++;
		free(key_w_eq);
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}
