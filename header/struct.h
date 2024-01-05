/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:11:36 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/04 15:33:39 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_environment
{
	char					*key;
	char					*value;
	struct s_environment	*next;
}	t_env;


typedef struct s_str_with_mode
{
	enum e_type				type;
	char					*value;
	struct s_str_with_mode	*next;
}	t_strm;

typedef struct s_amd
{
	struct s_str_with_mode	*str_mode;
	char					**command_line;
	char					**env;
	char					**path_env;
	char					*cmd_path;
	int						process_id;
	int						process_status;
	int						fd_in;
	int						fd_out;
	struct s_amd			*next;
}	t_cmd;

typedef struct s_token
{
	struct s_environment	*env_token;
	char					**env;
	char					*cur_input;
	int						return_code;
	char					*pid;
	int						command_count;
	char					*home_dir;
	struct s_amd			*command;
}	t_tok;
#endif