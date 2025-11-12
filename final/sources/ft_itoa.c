/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:10:12 by kedemiro          #+#    #+#             */
/*   Updated: 2025/06/26 17:36:05 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digits(int n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		digits = 1;
	while (n != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		digits;
	int		temp;

	temp = n;
	digits = ft_digits(n);
	result = malloc(sizeof(char) * digits + 1);
	if (!result)
		return (NULL);
	result[digits--] = '\0';
	if (temp == -2147483648)
	{
		result[digits--] = 8 + 48;
		temp = 214748364;
	}
	if (temp < 0)
		temp = -temp;
	while (digits >= 0)
	{
		result[digits--] = (temp % 10) + 48;
		temp /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
