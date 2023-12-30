/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:04:14 by tpoungla          #+#    #+#             */
/*   Updated: 2023/12/30 18:02:57 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_strm	*new_str_with_mode(char *str)
{
	t_strm	*new;

	if (!str)
		return (NULL);
	new = ft_calloc(sizeof(t_strm), 1);
	new->value = ft_strdup(str);
	new->type = def;
	new->next = NULL;
	return (new);
}

t_cmd	*new_command_tab(char *input, t_env *env)
{
	t_cmd	*new_table;
	t_strm	*set[3];
	char	**cmd_arg;
	int		i;

	if (!input)
		return (NULL);
	new_table = ft_calloc(sizeof(t_cmd), 1);
	cmd_arg = ft_split_sp(input, ' ');
	i = 0;
	set[0] = new_table->str_mode;
	while (cmd_arg[i])
	{
		if (i == 0)
		{
			set[0] = new_str_with_mode(cmd_arg[i]);
			set[1] = set[0];
		}
		else
		{
			set[2] = new_str_with_mode(cmd_arg[i]);
			set[0]->next = set[2];
			set[0] = set[2];
		}
		i++;
	}
	set_mode(set[1]);
	get_value_from_struct(set[1], env);
	if (cmd_arg)
		free2d(cmd_arg);
	new_table->fd_in = STDIN_FILENO;
	new_table->fd_out = STDOUT_FILENO;
	new_table->str_mode = set[1];
	return (new_table);
}

int	lexer_parser(t_tok *token, char *input)
{
	char	**split_cmd;
	int		i;
	t_cmd	*res;
	t_cmd	*new;

	split_cmd = ft_split_pipe(input, '|');
	if (split_cmd == NULL)
		return (1);
	i = 0;
	res = token->command;
	while (split_cmd[i])
	{
		if (i == 0)
		{
			new = new_command_tab(split_cmd[i], token->env_token);
			(*token).command = new;
			res = new;
		}
		else
		{
			new = new_command_tab(split_cmd[i], token->env_token);
			(*token).command->next = new;
			(*token).command = (*token).command->next;
		}
		i++;
	}
	(*token).command = res;
	free2d(split_cmd);
	return (0);
}
