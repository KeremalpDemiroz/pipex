/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 19:40:39 by kedemiro          #+#    #+#             */
/*   Updated: 2025/06/15 15:00:34 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;
	int				i;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	i = n - 1;
	if (src > dest)
	{
		ft_memcpy(ptr_dest, ptr_src, n);
	}
	else if (dest > src)
	{
		while (i >= 0)
		{
			ptr_dest[i] = ptr_src[i];
			if (i == 0)
				return (dest);
			i--;
		}
	}
	return (dest);
}
