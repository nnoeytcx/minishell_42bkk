/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:51:43 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/05 15:57:48 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#define CDAGUMENTS "minishell: cd: too many arguments\n"

int	ft_cd(char **param, t_tok *token)
{
	char	*old_pwd;
	char	*new_pwd;
	int		status;
	int		i;

	status = 0;
	i = 0;
	while (param[i])
		i++;
	if (i > 2)
		return (ft_putstr_fd(CDAGUMENTS, 2), 1);
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL && errno == ENOENT)
	{
		perror("getcwd : ");
		old_pwd = get_value_from_key("PWD", token->env_token);
	}
	if (i == 1)
	{
		if (-1 == chdir(token->home_dir))
			status = 1;
	}
	else
	{
		dprintf(2, "\nparam is [%s]\n", param[1]);
		if (is_same_str("~", param[1]))
		{
			if (-1 == chdir(token->home_dir))
				status = 1;
		}
		if (is_same_str("-", param[1]))
		{
			new_pwd = get_value_from_key("OLDPWD", token->env_token);
			if (-1 == chdir(new_pwd))
				status = 1;
			new_pwd = ft_free(new_pwd);
		}
		else 
		{
			if (-1 == chdir(param[1]))
				status = 1;
		}
	};
	dprintf(2, "status is == %d\n", status);
	if (status == 1)
		perror("CD : ");
	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL && errno == ENOENT && status == 0)
	{
		perror("getcwd : ");
		new_pwd = ft_strjoin(old_pwd ,"/.");
	};
	dprintf(2, "PWD : old [%s] new [%s]\n", old_pwd, new_pwd);
	if (status == 1)
		perror("CD : ");
	else
	{
		env_change_or_define("OLDPWD", old_pwd, token->env_token);
		env_change_or_define("PWD", new_pwd, token->env_token);
	}
	free(new_pwd);
	free(old_pwd);
	return (status);
}
