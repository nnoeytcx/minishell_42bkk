#include "../header/minishell.h"

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
        dprintf(2,"input [%s]\n", buff);
		if (0 != cflen && str_n_compare(buff, cutoffstr, cflen))
			break ;
		else if (buff[0] == '\n' && cflen == 0)
			break ;
        dprintf(2, "write to [%d]\n", fd[1]);
		write(fd[1], buff, ft_strlen(buff));
		free(buff);
	}
	free(buff);
	close(fd[1]);
	return (fd[0]);
}

void loop_and_assign_heredoc(t_cmd *t)
{
    t_cmd *tmp;
    t_strm *s_tmp;

    tmp = t;

    while (t)
    {
        s_tmp = t->str_mode;
        while (s_tmp)
        {
            if (s_tmp->type == h_doc_cut_str)
                t->fd_in = do_doctype(s_tmp->value);
            s_tmp = s_tmp->next;
        }
        t = t->next;
    }
}

int loop_open_file(t_cmd *t, int mode)
{
    int	fd;
    t_strm *lst;

    if (mode == OUT_FILE)
        fd = t->fd_out;
    if (mode == IN_FILE)
        fd = t->fd_in;
    lst = t->str_mode;
    while (lst)
    {
        if (mode == OUT_FILE)
        {
            if (lst->type == file_out_str)
            {
                fd = open(lst->value, O_RDWR | O_CREAT | O_TRUNC, 0664);
            }
            if (lst->type == file_out_append_str)
            {
                fd = open(lst->value, O_RDWR | O_CREAT | O_APPEND, 0664);
            }
        }
        if (mode == IN_FILE && lst->type == file_in_str)
            fd = open(lst->value, O_RDONLY);
        if (-1 == fd)
	    {
            perror("ERROR: ");
            dprintf(2, "U know what!!?? [%s] not found\n", lst->value);
            exit(1);
        };
        lst = lst->next;
    }
    
	return (fd);
}