/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:38:26 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/05 18:33:37 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"

struct sigaction sig;

void	signal_hunter(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("\n", 1);
		rl_redisplay();
		return ;
	}
	if (signal == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

char	*get_prompt(t_tok token)
{
	char	*tmps;
	char	*prompt;
	char	*ret_code;

	prompt = get_value_from_key("PWD", token.env_token); // wave
	dprintf(2,"pwd on prompt is [%s]\n", prompt); // wave
	if (prompt == NULL) // wave
		prompt = getcwd(NULL, 0);
    tmps = prompt;
    prompt = ft_strjoin(tmps, " $");
    tmps = ft_free(tmps);
    tmps = prompt;
    ret_code = ft_itoa(token.return_code);
    prompt = ft_strjoin(tmps, ret_code);
    tmps = ft_free(tmps);
    ret_code = ft_free(ret_code);
    tmps = prompt;
    prompt = ft_strjoin(tmps, " > ");
    tmps = ft_free(tmps);
    return (prompt);
}

char *readline_input(t_tok token)
{
	char	*input;
	char	*prompt;

	prompt = get_prompt(token);
	input = readline(prompt);
	if (input == NULL)
	{
		rl_clear_history();
		exit(1);
	}
	if (!(0 == ft_strlen(input)))
		add_history(input);
	// int i = 0;
	// ft_putstr_fd(prompt, 2);
	// int i = 0;
	// input = get_next_line(0);
	// dprintf(2, "input is [%s]\n",input);
	// while (input[i] && input[i] != '\n')
	// {
	// 	i++;
	// }
	// input[i] = '\0';
	// dprintf(2, "line is [%s]\n",input);
	// prompt = ft_free(prompt);
	return (input);	
}

int term_setup(int mode)
{
	struct termios terminal;

	if (mode == PARENT_PROCESS)
	{
		if (-1 == tcgetattr(STDERR_FILENO, &terminal))
			return (dprintf(2,"cannot get attr\n"));
		terminal.c_lflag &= ~ECHOCTL;
		if (-1 == tcsetattr(STDERR_FILENO, TCSANOW, &terminal))
			return (dprintf(2,"cannot set ttr\n"));
		sig.sa_handler = &signal_hunter;
		sig.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sig, NULL);
		sigaction(SIGQUIT, &sig, NULL);
	}
	else if (CHILD_PROCESS)
	{
		sig.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sig, NULL);
		sigaction(SIGQUIT, &sig, NULL);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_tok	token;

	(void) av;
	if (ac != 1 || !env)
		return (1);
	term_setup(PARENT_PROCESS);
	token.command = NULL;
	token.return_code = 0;
	token.env_token = init_env(env);
	dprintf(2, "pid is = [%d]\n", getpid());
	token.home_dir = get_value_from_key("HOME", token.env_token);
	while (1)
	{
		token.cur_input = readline_input(token);
		dprintf(2,"prompt == [%s]\n", token.cur_input);
		if (is_good_input(token.cur_input))
		{
			dprintf(2, "\033[1;33m------- PARSER -------\n");
			lexer_parser(&token, token.cur_input);
			//
			token.cur_input = ft_free(token.cur_input);
			dprintf(2,"----out of parser----\n\033[0;97m");
			print_tok(token);
			dprintf(2,"\n-----------------------------\n");
			dprintf(2,"\n\033[1;31m--------------[exe]--------------\n");
			token.return_code = execute_command(&token);
			dprintf(2,"\n---------------------------------\n");
			dprintf(2, "herasfasdfds\n");
			token.command = free_cmd_tab(token.command);
		}
		else
			token.cur_input = ft_free(token.cur_input);
	}
	free_token(&token);
	return (0);
}
