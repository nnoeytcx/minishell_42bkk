#include "minishell.h"

int run_token(t_tok token)
{

}

int get_env_token(t_env **t_env, char **env)
{

}

t_cmd	*make_token(t_tok	token, char	*input)
{
	
}

int main(int ac , char **av, char **env)
{
	(void) av;

	if (ac != 1 || !env) // << รับเเค่ รันโปรเเกรมโดยไม่ใส่ av ครับ "./minishell เท่านั้น"
		return (1);
	t_tok token;

	get_env_token(&token.env_token, env); //<<-- assign the env to key : value pair 
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
		add_history(input); // << กด ขึ้นเพื่อดู command ก่แนหน้าได้
		make_token(&token, input); // <<-- lexer parser
		run_token(token); //<< executor
		free_input_and_cmd_token(input, &token.command);
	}
}