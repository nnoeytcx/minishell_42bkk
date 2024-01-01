/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:11:17 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/01 17:32:07 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../header/library.h"

//error_parser.c
int				parser_error(char *str);

//expand.c
int				expand_from_env(t_strm *str_tab, t_env *env);
int				get_value_from_struct(t_strm *str_tab, t_env *env);
char			*find_dollarsign(char *str, t_env *env);
char			*get_expand(char *str_tab, t_env *env);
char			*trim_and_expand(char *str_tab, t_env *env);

//ft_split_pipe.c
char			**ft_split_pipe(char const *s, char c);
char			**get_split(char const *s, char c, char **res);
size_t			how_long(char const *s, char c);
size_t			count_on_me(char const *s, char c);

//ft_split_sp_util.c
char			get_quote_trigger(char quote_trigger, char const *s);
char const		*count_for_redirect(char const *s);
size_t			how_long_redirect(char const *s, size_t count);
int				is_redirect(char c);
int				is_quote(char c);

//ft_split_special.c
char			**ft_split_sp(char const *s, char c);
size_t			hhow_long(char const *s, char c);
size_t			ccount_on_me(char const *s);
char			**gget_split(char const *s, char c, char **res);

//parser.c
int				lexer_parser(t_tok *token, char *input);
t_cmd			*new_command_tab(char *input, t_env *env);
t_strm			*new_str_with_mode(char *str);

//print_tok.c
void			print_tok(t_tok t);
void			print_command_tab(t_cmd *cmd);
char			*get_newstr_expand(int num[2], char *new_str, char const *s, t_env *env);

//set_mode.c
int				set_mode(t_strm *str);
int				is_sp_symbol(char *str);

//expand_util.c
char			*get_new_str(char *str, t_env *env);
int				is_submeta(char c);
char			*my_ft_strjoin(char const *s1, char c2);
char			*ft_strjoy(char const *s1, char const *s2);
#endif