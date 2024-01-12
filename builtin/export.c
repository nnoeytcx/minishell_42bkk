/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:53:06 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/13 01:31:16 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	export_print(t_env *env_token)
{
	t_env	*tmp;

	if (env_token == NULL)
		return ;
	tmp = env_token;
	while (tmp)
	{
		printf("declare -x %s\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return ;
}

int	ft_export(char **param, t_tok *token)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (param[i])
		i++;
	if (i == 1)
		export_print(token->env_token);
	i = 1;
	while (param[i])
	{
		if (ft_strchr(param[i], '='))
		{
			key = getenv_key(param[i]);
			value = getenv_value(param[i]);
			if (key != NULL || value != NULL)
				env_change_or_define(key, value, token->env_token);
			key = ft_free(key);
			value = ft_free(value);
		}
		i++;
	}
	return (0);
}
