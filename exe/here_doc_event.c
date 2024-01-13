/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:12:08 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/13 22:06:10 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static volatile sig_atomic_t	g_signal;

static int	ch_stop_here(void)
{
	if (g_signal == 1)
	{
		rl_on_new_line();
		rl_replace_line("\n", 1);
		rl_redisplay();
		rl_done = 1;
	}
	return (0);
}

void	h_doc_hunter(int sig)
{
	if (sig == SIGINT)
		g_signal = 1;
}

void	doc_end_set(void)
{
	g_signal = 0;
	signal(SIGINT, &signal_hunter);
	rl_event_hook = NULL;
}

int	doc_first_init(int *cflen, char *cutoffstr, int fd[2])
{
	if (-1 == pipe(fd))
	{
		ft_putstr_fd("PIPE ERROR", 2);
		return (0);
	}
	*cflen = ft_strlen(cutoffstr);
	g_signal = 0;
	signal(SIGINT, &h_doc_hunter);
	rl_event_hook = ch_stop_here;
	return (1);
}

int	do_doctype(char *cutoffstr)
{
	char	*buff;
	int		fd[2];
	int		cflen;

	if (!doc_first_init(&cflen, cutoffstr, fd))
		return (-1);
	while (1)
	{
		buff = readline("> ");
		if ((buff == NULL || g_signal == 1) || \
			(0 != cflen && is_same_str(buff, cutoffstr)))
			break ;
		else if (cflen == 0)
			break ;
		write(fd[1], buff, ft_strlen(buff));
		write(fd[1], "\n", 1);
		buff = ft_free(buff);
	}
	doc_end_set();
	if (buff)
		buff = ft_free(buff);
	else
		fd[0] = here_doc_error(fd[0], cutoffstr);
	fd[1] = ft_close(fd[1]);
	return (fd[0]);
}
