/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:38:26 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 09:38:31 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"

char *get_prompt(t_tok token)
{
	char *temps_0;
	char *temps_1;
	char *prompt;

	temps_0 = get_value_from_key("USER", token.env_token);
	prompt = ft_strjoin("\033[1;31m", temps_0);
	free(temps_0);
	temps_0 = get_value_from_key("PWD", token.env_token);
	temps_1 = prompt;
	prompt = ft_strjoin(prompt, "\033[1;32m -> \033[1;34m");
	free(temps_1);
	temps_1 = prompt;
	prompt = ft_strjoin(prompt, temps_0);
	free(temps_1);
	free(temps_0);
	temps_0 = ft_itoa(token.return_code);
	temps_1 = prompt;
	prompt = ft_strjoin(prompt, " \033[1;33m$");
	free(temps_1);
	temps_1 = prompt;
	prompt = ft_strjoin(prompt,temps_0);
	free(temps_0);
	free(temps_1);
	temps_1 = prompt;
	prompt = ft_strjoin(prompt, "\033[1;37m > \033[0;97m");
	free(temps_1);
	return (prompt);
}

char *readline_input(t_tok token)
{
	char *input;
	char *pwd;
	// char *prompt;

	// prompt = get_prompt(token);
	// input = readline("minishell > "); //<< PROMPT in the header

	dprintf(2, "IN GNL;\n");
	input = get_next_line(0);
	// if (input == NULL) // << check case EOF or ^C kub 
	// {
	// 	rl_clear_history(); //<< safety 1st
	// 	exit(1); // << have to figure out the exit code later
	// }
	dprintf(2, "give promt\n");
	// if (!(0 == ft_strlen(input)))
	// 	add_history(input); // << กด ขึ้นเพื่อดู command ก่แนหน้าได้
	dprintf(2, "giveed promt\n");
	return (input);	
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_tok	token;

	if (ac != 1 || !env)
		return (1);
	token.command = NULL;
	token.return_code = 0;
	token.pid = get_pid();
	dprintf(2, "getpid\n");
	token.env_token = init_env(env);
	dprintf(2, "env init\n");
	while (1)
	{

		dprintf(2, "IN loop;\n");
		input = readline_input(token);
		dprintf(2,"prompt == [%s]\n", input);

		dprintf(2, "\033[1;33m------- PARSER -------\n");
		lexer_parser(&token, input);
		dprintf(2,"----out of parser----\n\033[0;97m");
		print_tok(token);
		dprintf(2,"\n-----------------------------\n");
		dprintf(2,"\n\033[1;31m--------------[exe]--------------\n");
		token.return_code = exe_command(&token);
		dprintf(2,"\n---------------------------------\n");
		free(input);
		input = NULL;
		free_cmd_tab(&token.command);
		token.command = NULL;
	}
	free_token(&token);
}