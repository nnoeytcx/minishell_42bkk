/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:43:39 by pruenrua          #+#    #+#             */
/*   Updated: 2022/08/31 20:48:07 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cp;
	char	*tcp;

	cp = (char *)malloc(sizeof (char) * ft_strlen(s1) + 1);
	if (cp == NULL)
		return (NULL);
	tcp = cp;
	while (*s1)
	{
		*tcp = *s1;
		tcp++;
		s1++;
	}
	*tcp = '\0';
	return (cp);
}
