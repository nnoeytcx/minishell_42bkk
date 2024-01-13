/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:11:17 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/13 13:35:50 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../header/library.h"

//error_parser.c
int				parser_error(char *str);
int				parser_error2(char c);
int				ft_check_meta(const char *c);
int				is_good_input(const char *c);

//in_file.c
char			*in_find(int num[4], char *new_str, \
				char *str, t_tok *token);
char			*in_trim(int num[4], char *new_str, \
				char *s, t_tok *token);
char			*in_expand(int num[4], char *new_str, \
				char *s, t_tok *token);
char			*get_join_c(char *new_str, char c);

//expand.c
int				get_value_from_struct(t_strm *str_tab, t_tok *token);
char			*find_dollarsign(char *str, t_tok *token);
char			*get_expand(char *str_tab, t_tok *token);
char			*trim_and_expand(char *str_tab, t_tok *token);
void			init_arr_number(int *arr, int a, int b, int c);

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
int				inside_ccount(char const *s, int skip, char qt, int *word);
char			**gget_split(char const *s, char c, char **res);

//parser.c
int				lexer_parser(t_tok *token, char *input);
void			init_table(t_cmd *table, t_strm *set);
t_cmd			*new_command_tab(char *input, t_tok *token);
t_strm			*new_str_with_mode(char *str);
void			free_me(char **res);

//print_tok.c
void			print_command_tab(t_cmd *cmd);
char			*get_newstr_expand(int num[2], char *new_str, \
				char const *s, t_tok *token);
int				check_quote_close(const char *c);
int				check_no_space(const char *c);

//set_mode.c
int				set_mode(t_strm *str);
int				ft_isspace(char c);
int				is_meta(char c);
char			*new_str_find(char *s, int num[2], t_tok *tok, char *new);
char			*new_str_find2(char *s, int num[2], t_tok *tok, char *new);

//expand_util.c
char			*get_new_str(char *str, t_tok *token);
int				is_submeta(char c);
char			*my_ft_strjoin(char *s1, char c2);
char			*ft_strjoy(char const *s1, char const *s2);
void			check_open_q(char c, int *num);

//util.c
int				in_check_meta(char **res, int i, char two);
void			set_type(t_strm *stm, int type, int next_type);
void			in_cmd_tab(t_strm	*set[3], char **cmd_arg, int i);
char			*joy_str(char *s, int num[2], char *new_str);
char			*new_str_getex(char *s, int num[2], t_tok *tok, char *new);
#endif