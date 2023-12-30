/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:07:54 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 14:41:16 by pruenrua         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "../header/library.h"

char	**free2d(char	**ptr);
t_tok	*free_token(t_tok *token);
t_cmd	*free_cmd_tab(t_cmd *cmd_tab);
t_env	*free_env_list(t_env *env_lst);
t_strm	*free_str_mode(t_strm *str_mode);
void	*ft_free(void	*ptr);
#endif