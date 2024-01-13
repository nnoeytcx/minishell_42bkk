/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:53:25 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/14 02:53:40 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*get_new_pwd(int status, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL && errno == ENOENT && status == 0)
	{
		ft_putstr_fd(CD_CR, 2);
		new_pwd = ft_strjoin(old_pwd, "/./");
	}
	return (new_pwd);
}

char	*get_old_pwd(t_tok *token)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL && errno == ENOENT)
	{
		old_pwd = get_value_from_key("PWD", token->env_token);
		if (old_pwd == NULL)
			old_pwd = ft_strdup(token->pwd);
	}
	return (old_pwd);
}
