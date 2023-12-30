/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exe_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:15:27 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 09:28:22 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	str_n_compare(const char *s1, const char *s2, size_t n)
{
	while (n)
	{
		if (*s1 != *s2)
			return (0);
		if (*s1 == 0)
			return (0);
		n--;
		s1++;
		s2++;
	}
	return (1);
}

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

char	**get_cmd(t_strm *str_list)
{
	t_strm	*tmp;
	char	**res;
	int		i;

	if (str_list == NULL)
		return (NULL);
	tmp = str_list;
	i = 0;
	while (tmp)
	{
		if (tmp->type == string)
			i++;
		tmp = tmp->next;
	}
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
