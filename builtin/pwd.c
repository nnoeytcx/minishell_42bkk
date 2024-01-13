/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:53:35 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/13 15:06:42 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_pwd(int mode, char **str, t_tok *token)
{
	char	*pwd_ret;

	pwd_ret = NULL;
	pwd_ret = getcwd(NULL, 0);
	if (pwd_ret == NULL && errno == ENOENT)
		pwd_ret = get_value_from_key("PWD", token->env_token);
	if (pwd_ret == NULL)
	{
		dprintf(2,"in NULL pwd\n");
		dprintf(2, "*str is == %s\n", *str);
		pwd_ret = ft_strdup(*str);
	}
	if (!pwd_ret)
		return (1);
	if (mode == PRINT)
	{
		printf("%s\n", pwd_ret);
		pwd_ret = ft_free(pwd_ret);
	}
	if (mode == GET)
	{
		*str = ft_free(*str);
		*str = pwd_ret;
	}
	return (0);
}
