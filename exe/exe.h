/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:24:13 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/07 21:16:21 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

# define IN_FILE 1
# define OUT_FILE 2
# define BUFFER_SIZE 1

# include "../header/library.h"
# define HERE_DOC_EOF_ERR "minishell: \
warning: here-document delimited by end-of-file (wanted "

int			here_doc_error(int fd, char *cut_str);
int			ft_close(int fd);
int			do_doctype(char *cutoffstr);
char		**get_cmd(t_strm *str_list);
char		*get_cmdpath(char *command, char **env);
char		**get_envpath(char **ep);
int			execute_command(t_tok *token);
void		errorcmd(t_cmd *t_c, t_tok *t, int errnum);
int			loop_open_file(t_cmd *t);
int			find_slash(char *str);
int			loop_and_assign_heredoc(t_cmd *t);
int			str_n_compare(const char *s1, const char *s2, size_t n);
int			count_command_tab(t_cmd *cmd);
void		parent_prepare_next_command(t_cmd *cur_cmd, \
									int pipo[2], int *tmp_fd);
int			wait_all_child(t_cmd *cmd_tab);
void		child_process_run(t_tok *t, t_cmd *cur_cmdtab, \
									int pipo[2], int fd_in);
void	run_command(t_cmd *t_c, t_tok *t);
#endif