/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:11:10 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/13 22:13:20 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./library.h"

void	signal_hunter(int signal);
void	put_errorcmd(char *str, char *cmd_p, char **cmd_a, int errnum);
int		term_setup(int mode);
void	init_token(t_tok *token, char **env);
void	minishell_init(t_tok *token, char **env);
char	*get_prompt(t_tok token);

#endif