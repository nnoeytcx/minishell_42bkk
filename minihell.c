#include "minishell.h"
typedef struct s_environment
{
	char *key;
	char *value;
	struct s_environment *next;
}	t_env;
typedef struct s_amd
{
	int redirect; // <----- redirect flag bool 0 is default if have redirect chage to 1
	int pipo[2];	// <--- for pipe init to [0,0]
	int fd_in;	// <------ default is 0 set by open after if have file_in;
	char *file_in; // <--- the file name that user pass in command (command < eiei.txt) want "eiei.txt"
	char **command;	// <-- the split command {"ls" , "-la", "......"}
	char *file_out; // <-- file out str for output (command > eiei.txt) want eiei.txt
	int fd_out;	// default 1 <set by open if have file_out
	struct	s_amd *next;
}	t_cmd ;

typedef struct s_token
{
	struct t_env 	*env_token; // <------ store env argument that pass by main (char **env) to use as minishell env
	char			**env; // <------- env to pass in to execve function must be char ** (join after token)
	struct t_cmd	*command;

}	t_tok; // <-- can change later kub

int main(int ac , char **av, char **env)
{
	(void) av;

	if (ac != 1 || !env)
		return (1);
	//t_tok token;
	while (1)
	{
		char *input;
		input = readline(PROMPT);
		if (input == NULL)
		{
			rl_clear_history();
			exit(1);
		}
		printf("input is [%s]\n", input);
		add_history(input);
		free(input);
	}
}