/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane < ubazzane@student.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:09:17 by ubazzane          #+#    #+#             */
/*   Updated: 2023/11/28 19:04:19 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	len;

	if (!str)
		return (ft_putstr("(null)"));
	len = ft_strlen(str);
	write(1, str, len);
	return (len);
}

int	ft_putnbr(long n)
{
	int	len;

	len = 0;
	if (n > 9 || n < -9)
		len += ft_putnbr(n / 10);
	else if (n < 0)
		len += ft_putchar('-');
	len += ft_putchar('0' + n % 10 * ((n > 0) - (n < 0)));
	return (len);
}

int	ft_puthex(unsigned long nbr, char format)
{
	char	*base;
	int		len;

	base = "0123456789abcdef";
	len = 0;
	if (nbr > 15)
		len += ft_puthex(nbr / 16, format);
	if (format == 'X' && ((nbr % 16) > 9))
		len += ft_putchar(base[nbr % 16] - 32);
	else
		len += ft_putchar (base[nbr % 16]);
	return (len);
}

int	ft_putptr(void *ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
	{
		len += ft_putstr("(nil)");
		return (len);
	}
	len += ft_putstr("0x");
	len += ft_puthex((unsigned long)ptr, 'x');
	return (len);
}
