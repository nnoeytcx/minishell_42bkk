/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:11:10 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/05 01:30:33 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./library.h"
// env_handle

char	*get_pid();
void	put_errorcmd(char *str, char *cmd_p, char **cmd_a, int errnum);
int term_setup(int mode);


#endif