/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:46:24 by kedemiro          #+#    #+#             */
/*   Updated: 2025/06/16 14:17:54 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size <= 0)
		return (src_len + size);
	i = 0;
	while ((i <= size -1) && dst[i] != '\0')
	{
		if ((dst[i] != '\0') && (i == size -1))
			return (src_len + size);
		i++;
	}
	i = 0;
	while ((i +1) <= (size - dst_len -1) && (src[i] != '\0'))
	{
		dst[dst_len + i] = src[i];
		i ++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
