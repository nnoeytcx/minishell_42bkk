/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:53:35 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/09 23:31:30 by pruenrua         ###   ########.fr       */
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
		pwd_ret = ft_strdup(token->pwd);
	if (!pwd_ret)
		return (1);
	if (mode == PRINT)
	{
		printf("%s\n", pwd_ret);
		pwd_ret = ft_free(pwd_ret);
	}
	if (mode == GET)
		*str = pwd_ret;
	return (0);
}
/* ref https://insanecoding.blogspot.com/2007/11/pathmax-simply-isnt.html*/