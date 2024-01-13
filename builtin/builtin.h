/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:49:52 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/14 02:53:05 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# define GET 1
# define PRINT 2
# define CDAGUMENTS "minishell: cd: too many arguments\n"
# define CD_CR "chdir: error retrieving current directory:\
	getcwd: cannot access parent directories: No such file or directory\n"

void	del_envlst_from_key(char *key, t_env **env_lst);
int		command_is_sin_builtin(t_cmd *t_c);
int		is_sin_builtin(char *cmd);
char	*get_new_pwd(int status, char *old_pwd);
char	*get_old_pwd(t_tok *token);
int		is_builtin(char *cmd);
int		run_builtin(char **cmd_lst, t_tok *token, int n);
int		run_single_builtin(t_tok *t);
int		command_is_builtin(t_cmd *t_c);
int		ft_env(t_env *env_list);
int		ft_pwd(int mode, char **str, t_tok *token);
int		ft_echo(char **param);
int		ft_cd(char **param, t_tok *token);
int		ft_exit(char **param, t_tok *token, int in);
int		ft_export(char **param, t_tok *token);
int		ft_unset(char **param, t_tok *token);
int		is_same_str(char *s1, char *s2);

#endif