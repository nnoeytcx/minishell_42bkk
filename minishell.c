/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:38:26 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 17:53:24 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"

char	*get_prompt(t_tok token)
{
	char	*tmps;
	char	*prompt;
	char	*ret_code;

	prompt = getcwd(NULL, 0);
    tmps = prompt;
    prompt = ft_strjoin(tmps, " $");
    free(tmps);
    tmps = prompt;
    ret_code = ft_itoa(token.return_code);
    prompt = ft_strjoin(tmps, ret_code);
    free(tmps);
    free(ret_code);
    tmps = prompt;
    prompt = ft_strjoin(tmps, " > ");
    free(tmps);
    return (prompt);
}

char *readline_input(t_tok token)
{
	char	*input;
	char	*prompt;

	prompt = get_prompt(token);
	input = readline(prompt); //<< PROMPT in the header
	if (input == NULL) // << check case EOF or ^C kub 
	{
		clear_history(); //<< safety 1st
		exit(1); // << have to figure out the exit code later
	}
	if (!(0 == ft_strlen(input)))
		add_history(input); // << กด ขึ้นเพื่อดู command ก่แนหน้าได้
	free(prompt);
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
	token.env_token = init_env(env);
	while (1)
	{
		input = readline_input(token);
		dprintf(2,"prompt == [%s]\n", input);
		//is_good_input();
		//ฟังชั่นดีหรือไม่()
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