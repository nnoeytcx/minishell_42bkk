/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:07:54 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 02:08:23 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "../header/library.h"

void	free2d(char	**ptr);
void	free_token(t_tok *token);
int		free_cmd_tab(t_cmd **cmd_tab);
int		free_env_list(t_env **env_lst);
int		free_str_mode(t_strm **str_mode);
#endif