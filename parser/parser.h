/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:11:17 by tpoungla          #+#    #+#             */
/*   Updated: 2023/12/26 15:32:22 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../header/library.h"

//error_parser.c
int				parser_error(char *str);

//expand.c
int				expand_from_env(t_strm *str_tab, t_env *env);
//void			trim_and_expand(char *str_tab);
//int				get_value_from_struct(t_strm *str_tab);
//void			get_expand(char *str_tab);

//ft_split_pipe.c
char			**ft_split_pipe(char const *s, char c);
static size_t	how_long(char const *s, char c);
static size_t	count_on_me(char const *s, char c);
char			**get_split(char const *s, char c, char **res);

//ft_split_sp_util.c
char			get_quote_trigger(char quote_trigger, char const *s);
char const		*count_for_redirect(char const *s);
size_t			how_long_redirect(char const *s, size_t count);
int				is_redirect(char c);
int				is_quote(char c);

//ft_split_special.c
char			**ft_split_sp(char const *s, char c);
size_t			hhow_long(char const *s, char c);
size_t			ccount_on_me(char const *s, char c);
char			**gget_split(char const *s, char c, char **res);

//parser.c
int				lexer_parser(t_tok *token, char *input);
t_cmd			*new_command_tab(char *input, t_env *env);
t_strm			*new_str_with_mode(char *str);

//print_tok.c
void			print_tok(t_tok t);
void			print_command_tab(t_cmd *cmd);

//set_mode.c
int				set_mode(t_strm *str);
int				is_sp_symbol(char *str);
#endif