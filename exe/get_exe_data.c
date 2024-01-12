/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exe_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:15:27 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/10 20:05:04 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	find_slash(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

char	**get_envpath(char **ep)
{
	if (!ep)
		return (NULL);
	while (*ep)
	{
		if (str_n_compare(*ep, "PATH=", 5))
			return (ft_split((*ep) + 5, ':'));
		ep++;
	}
	return (NULL);
}

char	*get_cmdpath(char *command, char **env)
{
	int		i;
	char	*prepath;
	char	*path_and_command;
	char	*ready_cmd;

	i = 0;
	if (!command)
		return (NULL);
	if (0 == access(command, X_OK) || env == NULL || find_slash(command))
	{
		ready_cmd = ft_substr(command, 0, ft_strlen(command));
		return (ready_cmd);
	}
	while (env[i])
	{
		prepath = ft_strjoin(env[i], "/");
		path_and_command = ft_strjoin(prepath, command);
		free(prepath);
		if (0 == access(path_and_command, X_OK))
			return (path_and_command);
		free(path_and_command);
		i++;
	}
	return (ft_substr(command, 0, ft_strlen(command)));
}

int	count_strmode(t_strm *str_lst, enum e_type mode)
{
	int		ret;
	t_strm	*tmp;

	ret = 0;
	tmp = str_lst;
	while (tmp)
	{
		if (tmp->type == mode)
			ret++;
		tmp = tmp->next;
	}
	return (ret);
}

char	**get_cmd(t_strm *str_list)
{
	t_strm	*tmp;
	char	**res;
	int		i;

	if (str_list == NULL)
		return (NULL);
	i = count_strmode(str_list, string);
	tmp = str_list;
	res = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (tmp)
	{
		if (tmp->type == string)
		{
			res[i] = ft_substr(tmp->value, 0, ft_strlen(tmp->value));
			i++;
		}
		tmp = tmp->next;
	}
	return (res);
}
