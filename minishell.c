#include "./header/minishell.h"


int g_signal = 0 ;

char *get_prompt(t_tok token)
{
	char *prompt;
	char *pwd;
	char *user;
	char *lst_status;
	char *tmp;
	
	user = get_value_from_key("USER", token.env_token);
	pwd = get_value_from_key("PWD", token.env_token);
	lst_status = ft_itoa(token.return_code);

	prompt = ft_strjoin("\033[1;31m", user);
	
	free(user);
	tmp = prompt;

	prompt = ft_strjoin(prompt, "\033[1;32m -> \033[1;34m");
	
	free(tmp);
	tmp = prompt;
	
	prompt = ft_strjoin(prompt, pwd);
	
	free(tmp);
	free(pwd);
	tmp = prompt;
	
	prompt = ft_strjoin(prompt, " \033[1;33m$");
	
	free(tmp);
	tmp = prompt;
	
	prompt = ft_strjoin(prompt, lst_status);
	
	free(lst_status);
	free(tmp);
	tmp = prompt;
	
	prompt = ft_strjoin(prompt, "\033[1;37m > \033[0;97m");
	free(tmp);

	return (prompt);
}
char *readline_input(t_tok token)
{
	char *input;
	char *pwd;
	char *prompt;

	prompt = get_prompt(token);
	dprintf(2,"\nprompt = [%s]\n", prompt);
	input = readline(prompt); //<< PROMPT in the header
	dprintf(2,"\nintput = [%s]\n", input);
	if (input == NULL) // << check case EOF or ^C kub 
	{
		rl_clear_history(); //<< safety 1st
		exit(1); // << have to figure out the exit code later
	}
	if (!(0 == ft_strlen(input)))
		add_history(input); // << กด ขึ้นเพื่อดู command ก่แนหน้าได้
	return (input);	
}

int main(int ac , char **av, char **env)
{
	char *input;
	t_tok token;

	if (ac != 1 || !env)
		return (1);
	token.command = NULL;
	token.return_code = 0;
	token.env_token = create_env(env); //<<-- assign the env to key : value pair 
	while (1)
	{
		input = readline_input(token);
		dprintf(2,"\nprompt == [%s]\n", input);
		lexer_parser(&token, input);
		dprintf(2,"\n--------out of parser--------\n");
		print_tok(token);
		dprintf(2,"\n-----------------------------\n");
		if (0 == ft_strncmp("env", input, 3))
			print_env(token);
		dprintf(2,"\n--------------[exe]--------------\n");
		token.return_code = exe_command(&token);
		dprintf(2,"\n---------------------------------\n");
		free(input);
		input = NULL;
		free_cmd_tab(&token.command);
		token.command = NULL;
	}
	free_token(&token);
}