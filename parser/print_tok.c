/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpoungla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:04:12 by tpoungla          #+#    #+#             */
/*   Updated: 2023/12/25 02:42:59 by tpoungla         ###   ########.fr       */
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
		printf("\n -----  {%d} cmd is [%p] -------\n", k, cmd);
		i = 0;
		while (stt)
		{
			printf("value [%s] mode [%d] -> ",stt->value, stt->type);
			stt = stt->next;
			i++;
		}
		printf("\nprocess id[%d]\n status[%d]\n", tmp->process_id, tmp->process_status);
		k++;
		tmp = tmp->next;
	}
	printf ("\n\n");
}

void	print_tok(t_tok t)
{
	printf("\n---------------token-----------\n");
	printf("--------vvvvvvv command tab---------\n");
	print_command_tab((t.command));
}
