#ifndef PARSER_H
#define PARSER_H

#include "../header/library.h"

int  set_mode(t_strm *str);
char    **ft_split_sp(char const *s, char c);
char	**ft_split_pipe(char const *s, char c);
int             expand_from_env(t_strm *str_tab, t_env *env);
t_cmd           *new_command_tab(char *input, t_env *env);
int             lexer_parser(t_tok *token, char *input);
t_strm      	*new_str_with_mode(char *str);
int         	in_value_split(t_strm *str);
int	            is_redirect(char c);
char const	    *count_for_redirect(char const *s);
char	        get_quote_trigger(char quote_trigger, char const *s);
int             parser_error(char *str);
void            print_tok(t_tok t);
#endif