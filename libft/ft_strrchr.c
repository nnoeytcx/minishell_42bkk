/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 09:23:20 by pruenrua          #+#    #+#             */
/*   Updated: 2022/08/31 20:17:03 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*las_oc;

	las_oc = 0;
	while (*s)
	{
		if (*s == (char)c)
			las_oc = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (las_oc);
}
