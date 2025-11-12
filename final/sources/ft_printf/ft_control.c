/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:13:29 by kedemiro          #+#    #+#             */
/*   Updated: 2025/07/09 05:43:18 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	ft_istype(const char *type, const char *str)
{
	if (*str == '%' && *(str + 1))
	{
		while (*type)
		{
			if (*type == *(str + 1))
				return (*type);
			type++;
		}
	}
	return (0);
}

int	ft_response(char c, va_list arg)
{
	if (c == 'c')
		return (ft_putchar((char)va_arg(arg, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(arg, char *)));
	else if (c == 'p')
		return (ft_puthex((unsigned long)va_arg(arg, void *), HEX_LOWER, c, 1));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(arg, int), BASE_DECIMAL));
	else if (c == 'u')
		return (ft_putunbr((unsigned int)va_arg(arg, int), BASE_DECIMAL));
	else if (c == 'x')
		return (ft_puthex(va_arg(arg, unsigned int), HEX_LOWER, c, 0));
	else if (c == 'X')
		return (ft_puthex(va_arg(arg, unsigned int), HEX_UPPER, c, 0));
	else if (c == '%')
		return (ft_putchar('%'));
	else
		return (0);
}
