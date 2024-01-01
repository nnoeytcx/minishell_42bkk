/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 00:04:05 by tpoungla          #+#    #+#             */
/*   Updated: 2023/12/31 09:11:28 by pruenrua         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	is_sp_symbol(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (0 == ft_strncmp(">", str, len))
		return (1);
	else if (0 == ft_strncmp("<", str, len))
		return (1);
	else if (0 == ft_strncmp("<<", str, len))
		return (1);
	return (0);
}

int	set_mode(t_strm *str)
{
	t_strm	*stm;
	int		len;

	if (!str)
		return (-1);
	stm = str;
	while (stm)
	{
		len = ft_strlen(stm->value);
		if (stm->type == string)
		{
			if (0 == ft_strncmp(">", stm->value, len))
			{
				stm->type = redout_symbol;
				if (stm->next && !is_sp_symbol(stm->next->value))
					stm->next->type = file_out_str;
				else
				{
					if (str->next)
						parser_error(str->next->value);
					else
						parser_error(NULL);
				}
			}
			else if (0 == ft_strncmp("<", stm->value, len))
			{
				stm->type = redin_symbol;
				if (stm->next && !is_sp_symbol(stm->next->value))
					stm->next->type = file_in_str;
				else
				{
					if (str->next)
						parser_error(str->next->value);
					else
						parser_error(NULL);
				}
			}
			else if (0 == ft_strncmp("<<", stm->value, len))
			{
				stm->type = h_doc_symbol;
				if (stm->next && !is_sp_symbol(stm->next->value))
					stm->next->type = h_doc_cut_str;
				else
				{
					if (str->next)
						parser_error(str->next->value);
					else
						parser_error(NULL);
				}
			}
			else if (0 == ft_strncmp(">>", stm->value, len))
			{
				stm->type = append_symbol;
				if (stm->next && !is_sp_symbol(stm->next->value))
					stm->next->type = file_out_append_str;
				else
				{
					if (str->next)
						parser_error(str->next->value);
					else
						parser_error(NULL);
				}
			}
		}
		dprintf(2, "set [%s] to [%d] mode\n", stm->value, stm->type);
		stm = stm->next;
	}
	return (1);
}
