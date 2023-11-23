#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"

#define ARG_STR 1
#define REDIR_IN 2
#define REDIR_OUT 3
#define DOUBLE_Q 4
#define SIN_Q_STR 5
#define EXPAN_STR 6
#define FILE_IN 7
#define FILE_OUT 8
#define HERE_DOC 9
#define DOC_CUT 10


#define SYNTAX_ERR "syntax error near unexpected token\n"
#define PROMPT "MINISHELL > "

#define FORK_ER "SYS : Can,t Fork\n"

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
	struct s_str_with_mode *next;
}	t_strm;

typedef struct s_amd
{
	struct s_str_with_mode *str_mode; //< the str with mode 
	int process_id;
	int process_status;
	int pipo[2];	// <--- for pipe init to [0,0]
	int fd_in;	// <------ default is 0 set by open after if have file_in;
	int fd_out;	// default 1 < set by open if have file_out
	char *file_in; // <--- the file name that user pass in command (command < eiei.txt) want "eiei.txt"
	char *file_out; // <-- file out str for output (command > eiei.txt) want eiei.txt
	struct	s_amd *next; // << next str = next node
}	t_cmd ;

typedef struct s_token
{
	struct s_environment 	*env_token; // <------ store env argument that pass by main (char **env) to use as minishell env
	char			**env; // <------- env to pass in to execve function must be char ** (join after token)
	struct s_amd	*command;

}	t_tok; // <-- can change later kub

// env_handle
char 	*get_value_from_key(char *key, t_env *token);
char	*getenv_value(char *env_v);
char	*getenv_key(char *env_v);
int		init_env_token(t_tok *token, char **env);
void	print_env(t_tok token);

int mock_up(t_tok *token, char *input);
void print_tok(t_tok t);
unsigned int exe_command(t_tok *token);

#endif