/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:35:42 by kedemiro          #+#    #+#             */
/*   Updated: 2025/06/25 16:38:05 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*temp;
	size_t			temp_len;

	temp_len = 0;
	i = 0;
	if (start >= ft_strlen(s))
	{
		temp = ft_strdup("");
		return (temp);
	}
	if (ft_strlen(s) - start < len)
		temp_len = ft_strlen(s) - start;
	else
		temp_len = len;
	temp = malloc(temp_len +1);
	if (!temp)
		return (NULL);
	while (i < temp_len && s[start + i] != '\0')
	{
		temp[i] = s[start + i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
