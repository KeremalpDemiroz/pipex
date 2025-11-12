/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:58:00 by kedemiro          #+#    #+#             */
/*   Updated: 2025/07/09 05:52:07 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <unistd.h>
# include <stdarg.h>

# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"
# define ARGS_TYPE "cspdiuxX%"
# define BASE_DECIMAL "0123456789"

int		ft_putchar(char c);
int		ft_putstr(const char *str);
int		ft_putnbr(int n, char *base);
int		ft_putunbr(unsigned int n, char *base);
int		ft_puthex(unsigned long n, const char *base, char type, int flag);
char	ft_istype(const char *type, const char *str);
int		ft_response(char c, va_list arg);
int		ft_printf(const char *string, ...);

#endif
