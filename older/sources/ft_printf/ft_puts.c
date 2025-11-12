/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:01:49 by kedemiro          #+#    #+#             */
/*   Updated: 2025/07/09 05:49:28 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (ft_putstr("(null)"));
	while (str[i] != '\0')
		write(1, &str[i++], 1);
	return (i);
}

int	ft_putunbr(unsigned int n, char *base)
{
	int	total;

	total = 0;
	if (n > 9)
		total += ft_putunbr(n / 10, base);
	total += ft_putchar(base[n % 10]);
	return (total);
}

int	ft_putnbr(int n, char *base)
{
	int	total;

	total = 0;
	if (n == -2147483648)
		return (ft_putstr("-2147483648"));
	else if (n < 0)
	{
		total += ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		total += ft_putnbr(n / 10, base);
	total += ft_putchar(base[n % 10]);
	return (total);
}

int	ft_puthex(unsigned long n, const char *base, char type, int flag)
{
	int	total;

	total = 0;
	if (type == 'p')
	{
		if (n == 0)
		{
			total += ft_putstr("(nil)");
			return (total);
		}
		if (flag)
		{
			total += ft_putstr("0x");
			flag = 0;
		}
		if (n > 15)
			total += ft_puthex(n / 16, base, type, flag);
		total += ft_putchar(base[n % 16]);
		return (total);
	}
	else if ((unsigned int)n > 15)
		total += ft_puthex((unsigned int)n / 16, base, type, flag);
	total += ft_putchar(base[(unsigned int)n % 16]);
	return (total);
}
