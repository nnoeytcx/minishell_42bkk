/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:38:26 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/13 22:13:37 by pruenrua         ###   ########.fr       */
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

char	*readline_input(t_tok token)
{
	char	*input;
	char	*prompt;

	prompt = get_prompt(token);
	input = readline(prompt);
	prompt = ft_free(prompt);
	if (input == NULL)
		return (NULL);
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

	if (ac != 1 || !env || av[1])
		return (1);
	minishell_init(&token, env);
	while (1)
	{
		ft_pwd(GET, &token.pwd, &token);
		token.cur_input = readline_input(token);
		if (token.cur_input == NULL)
			break ;
		if (is_good_input(token.cur_input))
		{
			lexer_parser(&token, token.cur_input);
			token.cur_input = ft_free(token.cur_input);
			token.return_code = execute_command(&token);
			token.command = free_cmd_tab(token.command);
		}
		token.cur_input = ft_free(token.cur_input);
	}
	free_token(&token);
	return (0);
}
