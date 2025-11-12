/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:13:27 by kedemiro          #+#    #+#             */
/*   Updated: 2025/06/16 17:12:26 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*cast_big;
	char	*cast_little;
	size_t	i;
	size_t	j;

	cast_big = (char *)big;
	cast_little = (char *)little;
	if (!(*cast_little))
		return (cast_big);
	i = 0;
	while (i +1 <= len && cast_big[i] != '\0')
	{
		j = 0;
		while ((cast_big[j + i] == cast_little[j])
			&& cast_little[j] != '\0' && (j + i) < len)
			j++;
		if (little[j] == '\0')
			return (&cast_big[i]);
		i++;
	}
	return (NULL);
}
