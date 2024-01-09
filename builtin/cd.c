/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:51:43 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/09 23:36:22 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
#define CDAGUMENTS "minishell: cd: too many arguments\n"

char	*get_new_pwd(int status, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL && errno == ENOENT && status == 0)
	{
		perror("getcwd : ");
		new_pwd = ft_strjoin(old_pwd, "/.");
	}
	return (new_pwd);
}

char	*get_old_pwd(t_tok *token)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL && errno == ENOENT)
	{
		perror("getcwd : ");
		old_pwd = get_value_from_key("PWD", token->env_token);
		if (old_pwd == NULL)
			old_pwd = ft_strdup(token->pwd);
	}
	return (old_pwd);
}

int	ch_old_pwd(t_env *env_tok)
{
	char	*old_pwd;
	int		ret;

	ret = 0;
	old_pwd = get_value_from_key("OLDPWD", env_tok);
	if (old_pwd == NULL)
	{
		ft_putstr_fd("OLDPWD not set\n", 2);
		return (-1);
	}
	ret = chdir(old_pwd);
	if (ret == -1)
	{
		ft_putstr_fd("minishell cd : ", 2);
		ft_putstr_fd(old_pwd, 2);
		perror(" : ");
	}
	old_pwd = ft_free(old_pwd);
	return (ret);
}

int	ft_chdir(char **param, t_tok *token)
{
	int	status;

	status = 0;
	if (!param[1])
		status = chdir(token->home_dir);
	else
	{
		if (is_same_str("~", param[1]))
			status = chdir(token->home_dir);
		else if (is_same_str("-", param[1]))
			status = ch_old_pwd(token->env_token);
		else
			status = chdir(param[1]);
	}
	//should add error;
	return (status);
}

int	check_arg(char **param)
{
	int	i;

	i = 0;
	while (param[i])
		i++;
	if (i > 2)
		return (0);
	return (1);
}

int	ft_cd(char **param, t_tok *token)
{
	char	*old_pwd;
	char	*new_pwd;
	int		status;

	status = 0;
	if (!check_arg(param))
		return (ft_putstr_fd(CDAGUMENTS, 2), 1);
	old_pwd = get_old_pwd(token);
	if (!(param + 1))
		status = chdir(token->home_dir);
	else
		status = ft_chdir(param, token);
	dprintf(2, "status is == %d\n", status);
	if (status == -1)
		perror("CD : ");
	new_pwd = get_new_pwd(status, old_pwd);
	dprintf(2, "PWD : old [%s] new [%s]\n", old_pwd, new_pwd);
	if (status != -1)
	{
		env_change_or_define("OLDPWD", old_pwd, token->env_token);
		env_change_or_define("PWD", new_pwd, token->env_token);
	}
	new_pwd = ft_free(new_pwd);
	old_pwd = ft_free(old_pwd);
	return (status);
}
