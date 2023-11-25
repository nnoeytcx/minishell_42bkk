#include "minishell.h"


int g_signal = 0 ;

int main(int ac , char **av, char **env)
{
	(void) av;

	//the env is char * with no \n
	if (ac != 1 || !env) // << รับเเค่ รันโปรเเกรมโดยไม่ใส่ av ครับ "./minishell เท่านั้น"
		return (1);
	t_tok token;

	token.command = NULL;
	init_env_token(&token, env); //<<-- assign the env to key : value pair 
	while (1)
	{
		char *input;
		input = readline(PROMPT); //<< PROMPT in the header
		if (input == NULL) // << check case EOF or ^C kub 
		{
			rl_clear_history(); //<< safety 1st
			exit(1); // << have to figure out the exit code later
		}
		printf("input is [%s]\n", input);
	//	printf("input is [%s]\n", input);
		mock_up(&token, input);
		print_tok(token);
		// printf("out mock\n");
		exe_command(&token);
		// print_tok(token);
		// printf("----------out mock-----------\n");
		// print_tok(token);
		if (!ft_strncmp(input, "env", ft_strlen("env")))
			print_env(token);
		if (!(0 == ft_strlen(input)))
			add_history(input); // << กด ขึ้นเพื่อดู command ก่แนหน้าได้
		// make_token(token, input); // <<-- lexer parser
		// run_token(token); //<< executor
		// free_input_and_cmd_token(input, &token.command);
	}
	// free_all_and_exit(token);
}