/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_from_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:01:52 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/14 03:56:24 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*getenv_value(char *env_v)
{
	char	*value;
	int		i;

	if (env_v == NULL)
		return (NULL);
	while (*env_v != '=')
		env_v++;
	if (!env_v)
		return (NULL);
	env_v++;
	value = ft_calloc(sizeof(char), ft_strlen(env_v) + 1);
	i = 0;
	while (env_v[i])
	{
		value[i] = env_v[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

char	*getenv_key(char *env_v)
{
	int		i;
	int		j;
	char	*key;

	if (env_v == NULL)
		return (NULL);
	i = 0;
	while (env_v[i] && env_v[i] == '=')
		i++;
	while (env_v[i] && env_v[i] != '=')
		i++;
	if (!env_v[i])
		return (NULL);
	key = ft_calloc(sizeof(char), i + 1);
	j = 0;
	while (env_v[j] && env_v[j] != '=')
	{
		key[j] = env_v[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

char	*get_value_from_key(char *key, t_env *token)
{
	t_env	*tmp;

	if (key == NULL)
		return (NULL);
	tmp = token;
	while (tmp)
	{
		if (is_same_str(key, tmp->key))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
