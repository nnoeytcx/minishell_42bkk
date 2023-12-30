/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:53:35 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 18:05:15 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_pwd(int mode, char **str)
{
	char	*pwd;
	char	*pwd_ret;

	pwd_ret = NULL;
	pwd_ret = getcwd(NULL, 0);
	if (pwd_ret == NULL && errno != ERANGE)
		return (perror("GETCWD : "), 1);
	if (mode == PRINT)
	{
		printf("%s\n", pwd_ret);
		free(pwd_ret);
	}
	if (mode == GET)
		*str = pwd;
	return (0);
}
/* ref https://insanecoding.blogspot.com/2007/11/pathmax-simply-isnt.html*/