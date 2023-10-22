/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:20:22 by pruenrua          #+#    #+#             */
/*   Updated: 2022/08/31 20:56:47 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tnext;

	while (*lst)
	{
		tnext = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tnext;
	}
	*lst = NULL;
}
