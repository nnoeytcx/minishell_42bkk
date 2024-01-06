/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:11:17 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/06 17:01:28 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../header/library.h"

//error_parser.c
int				parser_error(char *str);
int				ft_isspace(char c);
int				is_meta(char c);
int				check_quote_close(const char *c);
int				check_no_space(const char *c);
int				is_good_input(const char *c);
void			free_me(char **res);

//expand.c
int				expand_from_env(t_strm *str_tab, t_env *env);
int				get_value_from_struct(t_strm *str_tab, t_tok *token);
char			*find_dollarsign(char *str, t_tok *token);
char			*get_expand(char *str_tab, t_tok *token);
char			*trim_and_expand(char *str_tab, t_tok *token);

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

//print_tok.c
void			print_tok(t_tok t);
void			print_command_tab(t_cmd *cmd);
char			*get_newstr_expand(int num[2], char *new_str, \
				char const *s, t_tok *token);

//set_mode.c
int				set_mode(t_strm *str);
int				is_sp_symbol(char *str);

//expand_util.c
char			*get_new_str(char *str, t_tok *token);
int				is_submeta(char c);
char			*my_ft_strjoin(char const *s1, char c2);
char			*ft_strjoy(char const *s1, char const *s2);

//here_doc_na.c
char			*trim_and_expand_heredoc(char *str_tab, t_env *env);
#endif