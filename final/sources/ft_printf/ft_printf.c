/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 23:07:11 by kedemiro          #+#    #+#             */
/*   Updated: 2025/07/09 05:52:56 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_printf(const char *string, ...)
{
	va_list	arg;
	int		total;
	char	type;

	total = 0;
	va_start(arg, string);
	if (*string)
	{
		while (*string)
		{
			if (*string == '%')
			{
				type = ft_istype(ARGS_TYPE, string++);
				if (type)
					total += ft_response(type, arg);
			}
			else
				total += ft_putchar(*string);
			string++;
		}
	}
	va_end(arg);
	return (total);
}
