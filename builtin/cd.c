/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:51:43 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 14:16:59 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#define CDAGUMENTS "minishell: cd: too many arguments\n"

int	ft_cd(char **param, t_env *env_lst)
{
	char	*cwd;
	char	*old_pwd;
	char	*new_pwd;
	int		i;

	i = 0;
	while (param[i])
		i++;
	if (i > 2)
		return (ft_putstr_fd(CDAGUMENTS, 2), 1);
	old_pwd = getcwd(NULL, 0);
	if (i == 1)
	{
		if (-1 == chdir("~"))
			return (perror("minishell: cd: "), 1);
	}
	else if (-1 == chdir(param[1]))
	{
		return (perror("minishell: cd: "), 1);
	}
	new_pwd = getcwd(NULL, 0);
	dprintf(2, "PWD : old [%s] new [%s]\n", old_pwd, new_pwd);
	env_change_or_define("OLDPWD", old_pwd, env_lst);
	env_change_or_define("PWD", new_pwd, env_lst);
	free(new_pwd);
	free(old_pwd);
	return (0);
}
