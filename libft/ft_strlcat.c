/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 22:50:35 by pruenrua          #+#    #+#             */
/*   Updated: 2022/08/31 20:22:44 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lane_src;
	size_t	lane_dst;

	lane_src = ft_strlen(src);
	lane_dst = ft_strlen(dst);
	if (dstsize == 0 || lane_dst > dstsize - 1)
		return (lane_src + dstsize);
	dstsize = dstsize - 1;
	while (*dst && dstsize)
	{
		dst++;
		dstsize--;
	}
	while (*src && dstsize)
	{
		*dst = *src;
		dst++;
		src++;
		dstsize--;
	}
	*dst = '\0';
	return (lane_dst + lane_src);
}
