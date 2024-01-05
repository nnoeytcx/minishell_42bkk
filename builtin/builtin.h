/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:49:52 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/03 10:42:29 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# define GET 1
# define PRINT 2

int		is_builtin(char *cmd);
int		run_builtin(char **cmd_lst, t_tok *token);
int		run_single_builtin(t_tok *t);
int		command_is_builtin(t_cmd *t_c);
int		ft_env(t_env *env_list);
int		ft_pwd(int mode, char **str, t_tok *token);
int		ft_echo(char **param);
int		ft_cd(char **param, t_tok *token);
int		ft_exit(char **param, t_tok *token);
int		ft_export(char **param, t_tok *token);
int	is_same_str(char *s1, char *s2);

#endif