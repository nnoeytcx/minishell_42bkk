/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:15:29 by pruenrua          #+#    #+#             */
/*   Updated: 2022/08/31 20:01:54 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*sauce;
	size_t			i;

	if (!dst && !src)
		return (dst);
	sauce = (unsigned char *)src;
	dest = (unsigned char *)dst;
	if (sauce < dest && dest - sauce < (long)len)
	{
		i = len;
		while (i > 0)
		{
			dest[i - 1] = sauce[i - 1];
			i--;
		}
		return (dst);
	}
	else
		return (ft_memcpy(dest, src, len));
}
