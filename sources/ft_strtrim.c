/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:37:53 by kedemiro          #+#    #+#             */
/*   Updated: 2025/06/26 17:38:27 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	new_start(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	sw;

	j = 0;
	i = 0;
	sw = 1;
	while (sw)
	{
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
			{
				i++;
				j = 0;
			}
			else
				j++;
		}
		if (set[j] == '\0')
			sw = 0;
	}
	return (i);
}

static size_t	new_end(char const *s1, char const *set)
{
	size_t	size_s1;
	size_t	j;
	size_t	sw;

	j = 0;
	sw = 1;
	size_s1 = ft_strlen(s1) -1;
	while (sw)
	{
		j = 0;
		while (set[j] != '\0')
		{
			if (s1[size_s1] == set[j])
			{
				size_s1--;
				j = 0;
			}
			else
				j++;
		}
		if (set[j] == '\0')
			sw = 0;
	}
	return (size_s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	start = new_start(s1, set);
	if (start == ft_strlen(s1))
		return (ft_strdup(""));
	end = new_end(s1, set) - start;
	result = ft_substr(s1, start, (end + 1));
	return (result);
}
