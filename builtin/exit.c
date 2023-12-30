/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:52:56 by pruenrua          #+#    #+#             */
/*   Updated: 2023/12/30 01:52:58 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	ft_exit(char **param, t_tok *token)
{
	dprintf(2, "EXIT RUNNNNNNN\n");
	free_token(token);
	exit(0);
}