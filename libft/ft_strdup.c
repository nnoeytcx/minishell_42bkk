/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:43:39 by pruenrua          #+#    #+#             */
/*   Updated: 2024/01/05 14:39:17 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cp;
	char	*tcp;

	if (!s1)
		return (NULL);
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
