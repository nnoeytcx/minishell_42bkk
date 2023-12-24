#include "../header/minishell.h"

int	do_doctype(char *cutoffstr)
{
	char	*buff;
	int		fd[2];
	int		cflen;

	cflen = ft_strlen(cutoffstr);
	if (-1 == pipe(fd))
	{
		ft_putstr_fd("PIPE ERROR", 2);
		exit(1);
	}
	while (1)
	{
		write(1, "> ", 2);
		buff = get_next_line(0);
		if (0 != cflen && ft_strncmp(buff, cutoffstr, cflen))
			break ;
		else if (buff[0] == '\n' && cflen == 0)
			break ;
		write(fd[1], buff, ft_strlen(buff));
		free(buff);
	}
	free(buff);
	close(fd[1]);
	return (fd[0]);
}

int loop_open_file(t_strm *strm, int mode)
{
    int	fd;
    t_strm *lst;


    lst = strm;
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
        if (mode == IN_FILE)
        {
            if (lst->type == file_in_str)
            {
                fd = open(lst->value, O_RDONLY);
            }
            if (lst->type == h_doc_cut_str)
                fd = do_doctype(lst->value);
        }
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