/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 11:22:19 by kedemiro          #+#    #+#             */
/*   Updated: 2025/06/26 16:44:22 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	unsigned char	*cast_s;
	unsigned char	cast_c;
	size_t			i;

	cast_s = (unsigned char *)s;
	cast_c = (unsigned char)c;
	i = 0;
	if (len == 0)
		return (NULL);
	while (i < len)
	{
		if (cast_s[i] == cast_c)
			return (&cast_s[i]);
		i++;
	}
	return (NULL);
}
