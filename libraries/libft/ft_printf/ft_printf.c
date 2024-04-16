/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:08:10 by ubazzane          #+#    #+#             */
/*   Updated: 2024/03/04 19:35:28 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(const char format, va_list args);

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	len;

	if (!str)
		return (-1);
	va_start(args, str);
	len = 0;
	while (*str)
	{
		if (*str == '%')
			len += print_format(*(++str), args);
		else
			len += ft_putchar(*str);
		str++;
	}
	va_end(args);
	return (len);
}

int	print_format(const char format, va_list args)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (format == 'u')
		return (ft_putnbr(va_arg(args, unsigned int)));
	else if (format == 'X')
		return (ft_puthex(va_arg(args, unsigned int), 'X'));
	else if (format == 'x')
		return (ft_puthex(va_arg(args, unsigned int), 'x'));
	else if (format == '%')
		return (ft_putchar('%'));
	return (ft_putchar(format));
}
