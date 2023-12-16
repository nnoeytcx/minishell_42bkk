#include "./header/minishell.h"


int g_signal = 0 ;

char *readline_input(t_tok token)
{
	char *input;
	char *pwd;

	pwd = get_value_from_key("PWD", token.env_token);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(g_signal, 1);
	input = readline(" >"); //<< PROMPT in the header
	if (input == NULL) // << check case EOF or ^C kub 
	{
		rl_clear_history(); //<< safety 1st
		exit(1); // << have to figure out the exit code later
	}
	if (!(0 == ft_strlen(input)))
		add_history(input); // << กด ขึ้นเพื่อดู command ก่แนหน้าได้
	free(pwd);
	return (input);	
}

int main(int ac , char **av, char **env)
{
	char *input;
	t_tok token;

	if (ac != 1 || !env)
		return (1);
	token.command = NULL;
	token.env_token = create_env(env); //<<-- assign the env to key : value pair 
	while (1)
	{
		input = readline_input(token);
		lexer_parser(&token, input);
		if (0 == ft_strncmp("env", input, 3))
			print_env(token);
		g_signal = exe_command(&token);
		// free_input_and_cmd_token(input, &token.command);
		free(input);
		input = NULL;
		free_command_table(token.command);
		token.command = NULL;
	}
	// free_all_and_exit(token);
}