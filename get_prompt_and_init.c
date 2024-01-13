/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt_and_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:42:16 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/13 22:22:25 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"

char	*get_prompt(t_tok token)
{
	char	*tmps;
	char	*prompt;
	char	*ret_code;

	prompt = NULL;
	if (ft_pwd(GET, &prompt, &token))
		prompt = ft_strdup("minishell (PWD is MISSING but im still alive)");
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

void	init_token(t_tok *token, char **env)
{
	token->env_token = init_env(env);
	token->env = NULL;
	token->cur_input = NULL;
	token->command = NULL;
	token->pwd = NULL;
	token->home_dir = NULL;
	token->return_code = 0;
}

void	minishell_init(t_tok *token, char **env)
{
	char	*shell_level;
	int		shell_int;

	term_setup(PARENT_PROCESS);
	init_token(token, env);
	del_envlst_from_key("OLDPWD", &token->env_token);
	shell_level = get_value_from_key("SHLVL", token->env_token);
	if (!shell_level || (0 == ft_strlen(shell_level)))
		env_change_or_define("SHLVL", "1", token->env_token);
	else
	{
		shell_int = ft_atoi(shell_level);
		shell_int = shell_int + 1;
		shell_level = ft_free(shell_level);
		shell_level = ft_itoa(shell_int);
		env_change_or_define("SHLVL", shell_level, token->env_token);
		shell_level = ft_free(shell_level);
	}
}
