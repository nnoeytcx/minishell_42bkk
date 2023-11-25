#ifndef STRUCT_H
#define STRUCT_H

typedef struct s_environment // <<-- fot the env glob;e variable 
{
	char *key;
	char *value;
	struct s_environment *next;
}	t_env;


typedef struct s_str_with_mode
{
	enum type type;
	char	  *value;
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

#endif