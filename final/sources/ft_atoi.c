/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:08:01 by kedemiro          #+#    #+#             */
/*   Updated: 2025/06/26 14:51:08 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	char	*cast;
	int		sign;
	int		result;
	int		i;

	i = 0;
	result = 0;
	sign = 1;
	cast = (char *)nptr;
	while ((cast[i] >= 9 && cast[i] <= 13) || cast[i] == 32)
		i++;
	if (cast[i] == '-' || cast[i] == '+')
	{
		if (cast[i] == '-')
			sign *= -1;
		i++;
	}
	while (cast[i] >= '0' && cast[i] <= '9')
	{
		result = (result * 10) + (cast[i] - 48);
		i++;
	}
	result *= sign;
	return (result);
}
