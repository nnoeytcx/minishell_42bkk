/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:38:26 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/08 21:07:25 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"

static volatile sig_atomic_t	g_signal;

void	signal_hunter(int signal)
{
	if (signal == SIGINT && g_signal == 0)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (signal == SIGQUIT)
		return ;
}

char	*get_prompt(t_tok token)
{
	char	*tmps;
	char	*prompt;
	char	*ret_code;

	prompt = get_value_from_key("PWD", token.env_token);
	if (prompt == NULL)
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

char	*readline_input(t_tok token)
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
	return (input);
}

int	term_setup(int mode)
{
	struct termios		terminal;
	struct sigaction	sig;

	if (mode == PARENT_PROCESS)
	{
		g_signal = 0;
		if (-1 == tcgetattr(STDERR_FILENO, &terminal))
			return (ft_putstr_fd("cannot get attr\n", 2), 1);
		terminal.c_lflag &= ~ECHOCTL;
		if (-1 == tcsetattr(STDERR_FILENO, TCSANOW, &terminal))
			return (ft_putstr_fd("cannot set ttr\n", 2), 1);
		ft_bzero(&sig, sizeof(sigaction));
		sigemptyset(&sig.sa_mask);
		sig.sa_handler = &signal_hunter;
		sig.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sig, NULL);
		sigaction(SIGQUIT, &sig, NULL);
		ft_bzero(&sig, sizeof(sigaction));
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
	token.home_dir = get_value_from_key("HOME", token.env_token);
	while (1)
	{
		token.cur_input = readline_input(token);
		dprintf(2,"prompt == [%s]\n", token.cur_input);
		if (is_good_input(token.cur_input))
		{
			dprintf(2, "\033[1;33m------- PARSER -------\n");
			lexer_parser(&token, token.cur_input);
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
