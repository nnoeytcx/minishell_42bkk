#ifndef DEFINE_VAR_H
#define DEFINE_VAR_H

enum e_type {
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

#define DEFAULT_PATH_VALUE "/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin:."
// should define according to bash when the env isn't have the PATH variable when run the bash PATH should set to this value 
// see bash/config.h to see more --> https://github.com/bminor/bash/blob/8868edaf2250e09c4e9a1c75ffe3274f28f38581/config-top.h#L65

#define SYNTAX_ERR "Minishell:  syntax error near unexpected token `"
#define PROMPT "MINISHELL "

#define FORK_ER "SYS : Can,t Fork\n"
#define O_WSTR 0
#define O_KEYV 1

#endif