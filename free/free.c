/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:06:06 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/12 13:06:24 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

char	**free2d(char	**ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (NULL);
	while (ptr[i])
	{
		ptr[i] = ft_free(ptr[i]);
		i++;
	}
	ptr = ft_free(ptr);
	return (NULL);
}