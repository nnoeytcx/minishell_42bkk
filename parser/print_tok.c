/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:04:12 by tpoungla          #+#    #+#             */
/*   Updated: 2023/12/30 18:03:14 by tpoungla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	print_command_tab(t_cmd *cmd)
{
	int		i;
	int		k;
	t_cmd	*tmp;
	t_strm	*stt;

	i = 0;
	k = 0;
	tmp = cmd;
	while (tmp != NULL)
	{
		stt = tmp->str_mode;
		printf("\n - {%d} cmd [%p] -\n\n", k, cmd);
		i = 0;
		while (stt)
		{
			printf("[%s] mode [%d] -> ", stt->value, stt->type);
			stt = stt->next;
			i++;
		}
		printf("\n\npid[%d]\nstatus[%d]", tmp->process_id, tmp->process_status);
		k++;
		tmp = tmp->next;
	}
	printf ("\n\033[0;97m");
}

void	print_tok(t_tok t)
{
	printf("\n\033[1;34m-----token-----\n");
	print_command_tab((t.command));
}
