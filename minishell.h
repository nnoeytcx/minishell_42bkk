#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define ARG_STR 1
#define REDIR_IN 2
#define REDIR_OUT 3

#define HERE_DOC 9
#define DOC_CUT 10
#define FILE_IN 7
#define FILE_OUT 8

#define DOUBLE_Q 4
#define SIN_Q_STR 5
#define EXPAN_STR 6

#define SYNTAX_ERR "syntax error near unexpected token"

typedef struct s_environment // <<-- fot the env glob;e variable 
{
	char *key;
	char *value;
	struct s_environment *next;
}	t_env;


typedef struct s_str_with_mode
{
	int		mode;
	char	*value;
	s_str_with_mode *next;
} t_strm;

typedef struct s_amd
{
	t_strm *str_mode; //< the str with mode 
	int pipo[2];	// <--- for pipe init to [0,0]
	int fd_in;	// <------ default is 0 set by open after if have file_in;
	int fd_out;	// default 1 < set by open if have file_out
	char *file_in; // <--- the file name that user pass in command (command < eiei.txt) want "eiei.txt"
	char *file_out; // <-- file out str for output (command > eiei.txt) want eiei.txt
	struct	s_amd *next; // << next str = next node
}	t_cmd ;

typedef struct s_token
{
	struct t_env 	*env_token; // <------ store env argument that pass by main (char **env) to use as minishell env
	char			**env; // <------- env to pass in to execve function must be char ** (join after token)
	struct t_cmd	*command;

}	t_tok; // <-- can change later kub


#define PROMPT "MINISHELL > "
#endif