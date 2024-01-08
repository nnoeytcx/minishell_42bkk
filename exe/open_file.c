/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:28:53 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/08 20:57:47 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	open_infile(char *filename, int *status)
{
	int	fd;

	fd = open(filename, O_RDONLY | O_CLOEXEC);
	if (-1 == fd)
	{
		*status = 0;
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (fd);
}

int	open_outfile(char *filename, int mode, int *status)
{
	int	fd;

	if (mode == O_TRUNC)
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0664);
	if (mode == O_APPEND)
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND | O_CLOEXEC, 0664);
	if (-1 == fd)
	{
		*status = 0;
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

int	loop_open_file(t_cmd *t)
{
	t_strm	*lst;
	int		status;

	status = 1;
	lst = t->str_mode;
	if (t->fd_in > 2)
		dup2(t->fd_in, STDIN_FILENO);
	while (lst)
	{
		if (lst->type == file_out_str)
			open_outfile(lst->value, O_TRUNC, &status);
		if (lst->type == file_out_append_str)
			open_outfile(lst->value, O_APPEND, &status);
		if (lst->type == file_in_str)
			open_infile(lst->value, &status);
		lst = lst->next;
	}
	return (status);
}

int	here_doc_error(int fd, char *cut_str)
{
	close(fd);
	ft_putstr_fd(HERE_DOC_EOF_ERR, 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(cut_str, 2);
	ft_putstr_fd("')", 2);
	return (-1);
}

int	loop_and_assign_heredoc(t_cmd *t)
{
	t_strm	*s_tmp;

	while (t)
	{
		s_tmp = t->str_mode;
		while (s_tmp)
		{
			if (s_tmp->type == h_doc_cut_str)
				t->fd_in = do_doctype(s_tmp->value);
			if (t->fd_in == -1)
				return (0);
			s_tmp = s_tmp->next;
		}
		t = t->next;
	}
	return (1);
}