/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:24:13 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/31 20:01:11 by pruenrua         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

# define IN_FILE 1
# define OUT_FILE 2
# define BUFFER_SIZE 1

# include "../header/library.h"

char			**get_cmd(t_strm *str_list);
char			*get_cmdpath(char *command, char **env);
char			**get_envpath(char **ep);
unsigned int	exe_command(t_tok *token);
void			errorcmd(t_cmd *t_c, t_tok *t, int errnum);
int				loop_open_file(t_cmd *t);
char			*get_next_line(int fd);
int				find_slash(char *str);
int				loop_and_assign_heredoc(t_cmd *t);
int				str_n_compare(const char *s1, const char *s2, size_t n);
#endif