/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 09:03:08 by pruenrua          #+#    #+#             */
/*   Updated: 2022/08/31 20:00:45 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*t_des;

	if (!dst && !src)
		return (dst);
	t_des = dst;
	while (n)
	{
		*t_des = *(unsigned char *)src;
		t_des++;
		src++;
		n--;
	}
	return (dst);
}
