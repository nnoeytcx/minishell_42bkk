/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 20:55:22 by pruenrua          #+#    #+#             */
/*   Updated: 2022/08/31 20:33:06 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	need_len;
	size_t	need_index;

	if (!*needle)
		return ((char *)haystack);
	need_len = ft_strlen(needle);
	while (*haystack && len)
	{
		if (need_len > len)
			return (NULL);
		need_index = 0;
		while (*(needle + need_index) == *(haystack + need_index))
		{
			if (need_index + 1 == need_len)
				return ((char *)haystack);
			need_index++;
		}
		haystack++;
		len--;
	}
	return (NULL);
}
