/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:31:34 by kedemiro          #+#    #+#             */
/*   Updated: 2025/06/25 13:45:18 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		i;

	tmp = (char *)s;
	i = ft_strlen((const char *)tmp);
	if (c == '\0')
		return (&tmp[i]);
	while (i >= 0)
	{
		if (tmp[i] == (char)c)
			return (&tmp[i]);
		i--;
	}
	return (NULL);
}
