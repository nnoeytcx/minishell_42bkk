/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_from_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:01:52 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 18:18:02 by tpoungla         ###   ########.fr       */
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
	env_v++;
	value = ft_calloc(sizeof(char), (1 + ft_strlen(env_v)));
	i = 0;
	while (env_v[i])
	{
		value[i] = env_v[i];
		i++;
	}
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
	while (env_v[i] != '=')
		i++;
	key = ft_calloc(sizeof(char), ft_strlen(env_v));
	j = 0;
	while (env_v[j] != '=')
	{
		key[j] = env_v[j];
		j++;
	}
	return (key);
}

char	*get_value_from_key(char *key, t_env *token)
{
	t_env	*tmp;

	if (key == NULL)
		return (NULL);
	printf("key : %s\n", key);
	tmp = token;
	while (tmp->next)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(key)))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
