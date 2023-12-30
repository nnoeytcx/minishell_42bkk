/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:11:36 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 02:14:42 by pruenrua         ###   ########.fr       */
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
	int						return_code;
	char					*pid;
	struct s_amd			*command;
}	t_tok;

#endif