/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 12:51:02 by pruenrua          #+#    #+#             */
/*   Updated: 2022/08/31 20:48:36 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subbstr;
	size_t	i;

	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s + start);
	subbstr = malloc(len + 1);
	if (!subbstr)
		return (0);
	i = 0;
	while (len - i && start + i < ft_strlen(s))
	{
		*(subbstr + i) = *(s + (start + i));
		i++;
	}
	*(subbstr + i) = '\0';
	return (subbstr);
}
