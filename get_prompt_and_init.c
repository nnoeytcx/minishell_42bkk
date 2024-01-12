/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt_and_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:42:16 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/12 23:49:29 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"

char	*get_prompt(t_tok token)
{
	char	*tmps;
	char	*prompt;
	char	*ret_code;

	if (ft_pwd(GET, &prompt, &token))
		prompt = ft_strdup("minishell (PWD is MISSING)");
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
