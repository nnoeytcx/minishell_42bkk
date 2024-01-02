/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:28:53 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/02 23:56:40 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	here_doc_error(int fd, char *cut_str)
{
	close(fd);
	ft_putstr_fd("bash: warning: here-document delimited by end-of-file (wanted ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(cut_str, 2);
	ft_putstr_fd("')", 2);
	return (-1);
}

int	do_doctype(char *cutoffstr)
{
	char	*buff;
	int		fd[2];
	int		cflen;

	cflen = ft_strlen(cutoffstr);
    dprintf(2, "in here_doc cut set == [%s]\n", cutoffstr);
	if (-1 == pipe(fd))
	{
		ft_putstr_fd("PIPE ERROR", 2);
		exit(1);
	}
	while (1)
	{
		write(1, "> ", 2);
		buff = get_next_line(0);
		if (buff == NULL)
			break;
		if (0 != cflen && str_n_compare(buff, cutoffstr, cflen))
			break ;
		else if (buff[0] == '\n' && cflen == 0)
			break ;
		write(fd[1], buff, ft_strlen(buff));
		buff = ft_free(buff);
	}
	if (buff)
		buff = ft_free(buff);
	else
		fd[0] = here_doc_error(fd[0], cutoffstr);
	fd[1] = ft_close(fd[1]);
	return (fd[0]);
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

int open_infile(char *filename, int *status)
{
	int	fd;
	
	ft_putstr_fd("open[",2);
	ft_putstr_fd(filename,2);
	ft_putstr_fd("] in infilee\n",2);
	fd = open(filename, O_RDONLY | O_CLOEXEC);
	if (-1 == fd)
	{
		perror("ERROR: ");
		dprintf(2, "U know what!!?? [%s] not found\n", filename);
		*status = 1;
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (fd);
}

int	open_outfile(char *filename, int mode, int *status)
{
	int	fd;

	ft_putstr_fd("open[",2);
	ft_putstr_fd(filename,2);
	ft_putstr_fd("] in outfile\n",2);
	if (mode == O_TRUNC)
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0664);
	if (mode == O_APPEND)
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND | O_CLOEXEC, 0664);
	if (-1 == fd)
	{
		perror("ERROR: ");
		dprintf(2, "U know what!!?? [%s] not found\n", filename);
		*status = 1;
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (fd);
}

int	loop_open_file(t_cmd *t)
{
	t_strm	*lst;
	int		status;

	status = 0;
	ft_putstr_fd("\n---------- open loop -------\n\n",2);
	lst = t->str_mode;
	while (lst)
	{
		if (status)
			return (0);
		if (lst->type == file_out_str)
			open_outfile(lst->value, O_TRUNC, &status);
		if (lst->type == file_out_append_str)
			open_outfile(lst->value, O_APPEND, &status);
		if (lst->type == file_in_str)
			open_infile(lst->value, &status);
		lst = lst->next;
	}
	return (1);
}


// int	loop_open_file(t_cmd *t)
// {
// 	int		fd[2];
// 	int		tmp[2];
// 	int		new_fd[2];
// 	t_strm	*lst;

// 	new_fd[1] = t->fd_out;
// 	new_fd[0] = t->fd_in;
// 	lst = t->str_mode;
// 	while (lst)
// 	{
//         if (lst->type == file_out_str)
// 			tmp[1] = open(lst->value, O_RDWR | O_CREAT | O_TRUNC, 0664);
//         if (lst->type == file_out_append_str)
//             tmp[0] = open(lst->value, O_RDWR | O_CREAT | O_APPEND, 0664);
// 		if (lst->type == file_in_str)

// 		if (tmp[0] == -1 || tmp[1] == -1)
// 	    {
// 			perror("ERROR: ");
// 			dprintf(2, "U know what!!?? [%s] not found\n", lst->value);
// 			exit(1);
// 		}
// 		else
// 		{
// 			if (new_fd[1] != STDOUT_FILENO)
// 				dup2(tmp[1], new_fd[1]);
// 			else
// 				new_fd[1] = tmp[1];
// 			if (new_fd[0] != STDIN_FILENO)
// 				dup2(tmp[0], new_fd[1]);
// 			else
// 				new_fd[0] = tmp[1];
// 		}
// 		lst = lst->next;
// 	}
// 	return (fd);
// }

