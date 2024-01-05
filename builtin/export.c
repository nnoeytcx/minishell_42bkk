/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:53:06 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/05 14:43:24 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_export(char **param, t_tok *token)
{
	int i;
	char *key;
	char *value;

	i = 0;
	dprintf(2, "in exporttttttt\n");
	while (param[i])
		i++;
	if (i < 2)
		export_print(token->env_token);
	i++;
	while (param[i])
	{
		if (isparam_valid(param[i]))
		{
			key = getenv_key(param[i]);
			value = getenv_value(param[i]);
			if (key != NULL)
				env_change_or_define(key, value, token->env_token);
			key = ft_free(key);
			value = ft_free(value);
		}
		i++;
	}
	return (0);
}