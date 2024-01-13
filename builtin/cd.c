/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:51:43 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/14 02:49:15 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ch_old_pwd(t_env *env_tok)
{
	char	*old_pwd;
	int		ret;

	ret = 0;
	old_pwd = get_value_from_key("OLDPWD", env_tok);
	if (old_pwd == NULL)
	{
		ft_putstr_fd("minishell : cd: OLDPWD not set\n", 2);
		return (-1);
	}
	ret = chdir(old_pwd);
	if (ret == -1)
	{
		ft_putstr_fd("minishell : cd : ", 2);
		ft_putstr_fd(old_pwd, 2);
		perror(" : ");
	}
	else
		printf("%s\n", old_pwd);
	old_pwd = ft_free(old_pwd);
	return (ret);
}

int	ft_chdir(char **param, t_tok *token)
{
	int		status;
	char	*home;

	status = 0;
	if (!param[1])
	{
		home = get_value_from_key("HOME", token->env_token);
		status = chdir(home);
		if (status == -1)
			ft_putstr_fd("minishell : cd : HOME not set\n", 2);
	}
	else
	{
		if (is_same_str("-", param[1]))
			return (ch_old_pwd(token->env_token));
		else if (ft_strlen(param[1]) > 0)
			status = chdir(param[1]);
		if (status == -1)
		{
			ft_putstr_fd("minishell : cd : ", 2);
			ft_putstr_fd(param[1], 2);
			perror(" ");
		}
	}
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
		return (ft_putstr_fd(CDAGUMENTS, 2), 2);
	old_pwd = get_old_pwd(token);
	status = ft_chdir(param, token);
	new_pwd = get_new_pwd(status, old_pwd);
	if (status != -1)
	{
		env_change_or_define("OLDPWD", old_pwd, token->env_token);
		env_change_or_define("PWD", new_pwd, token->env_token);
	}
	new_pwd = ft_free(new_pwd);
	old_pwd = ft_free(old_pwd);
	if (status == -1)
		status = 1;
	return (status);
}
