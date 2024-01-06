/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:04:14 by tpoungla          #+#    #+#             */
/*   Updated: 2024/01/06 17:13:50 by pruenrua         ###   ########.fr       */
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

void	init_table(t_cmd *table, t_strm *set)
{
	if (!table)
		return ;
	table->str_mode = set;
	table->command_line = NULL;
	table->env = NULL;
	table->path_env = NULL;
	table->cmd_path = NULL;
	table->process_id = -1;
	table->process_status = -1;
	table->fd_in = STDIN_FILENO;
	table->fd_out = STDOUT_FILENO;
	table->next = NULL;
}

t_cmd	*new_command_tab(char *input, t_tok *token)
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
	get_value_from_struct(set[1], token);
	set_mode(set[1]);
	if (cmd_arg)
		free2d(cmd_arg);
	init_table(new_table, set[1]);
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
		new = new_command_tab(split_cmd[i], token);
		if (i == 0)
		{
			(*token).command = new;
			res = new;
		}
		else
		{
			(*token).command->next = new;
			(*token).command = (*token).command->next;
		}
		i++;
	}
	dprintf(2, "malloc [%d]\n", i);
	(*token).command = res;
	free2d(split_cmd);
	return (0);
}
