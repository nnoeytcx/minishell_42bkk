#ifndef DEFINE_VAR_H
#define DEFINE_VAR_H

enum type {
    def = 0,
    string,
    variable,
    double_quote_str,
    single_quote_str,
    file_in_str,
    file_out_str,
    file_out_append_str,
    h_doc_cut_str,
    h_doc_symbol,
    append_symbol,
    redin_symbol,
    redout_symbol,
    redin_append_symbol
};

#define DEF_VAL 0
#define ARG_STR 1

#define REDIR_IN 2
#define REDIR_OUT 3

#define DOUBLE_Q 4
#define SIN_Q_STR 5

#define VAR_STR 6

#define FILE_IN 7
#define FILE_OUT 8
#define FILE_OUT_APPEND 11
#define FILE_OUT_APPEND_SY 12

#define HERE_DOC 9
#define DOC_CUT 10

#define SYNTAX_ERR "Minishell:  syntax error near unexpected token `"
#define PROMPT "MINISHELL > "

#define FORK_ER "SYS : Can,t Fork\n"

#endif