/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:53:35 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/03 10:43:12 by pruenrua         ###   ########.fr       */
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
	if (mode == PRINT)
	{
		printf("%s\n", pwd_ret);
		free(pwd_ret);
	}
	if (mode == GET)
		*str = pwd_ret;
	return (0);
}
/* ref https://insanecoding.blogspot.com/2007/11/pathmax-simply-isnt.html*/