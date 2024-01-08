/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_var.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 02:08:42 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/08 20:59:33 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_VAR_H
# define DEFINE_VAR_H

typedef enum e_type
{
	def = 0,
	string,
	variable,
	double_quote_str,
	single_quote_str,
	here_str,
	file_in_str,
	file_out_str,
	file_out_append_str,
	h_doc_cut_str,
	h_doc_symbol,
	append_symbol,
	redin_symbol,
	redout_symbol,
	redin_append_symbol
}	t_type;

# define SYNTAX_ERR "Minishell:  syntax error near unexpected token `"
# define PROMPT "MINISHELL "
# define SP_TOKEN "< > << >> $ |"
# define QUOTE_TOKEN "\"\'"
# define FORK_ER "SYS : Can,t Fork\n"
# define O_WSTR 0
# define O_KEYV 1
# define PARENT_PROCESS 1
# define CHILD_PROCESS 2

#endif