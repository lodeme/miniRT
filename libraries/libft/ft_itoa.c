/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane < ubazzane@student.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:38:18 by ubazzane          #+#    #+#             */
/*   Updated: 2023/11/17 16:40:18 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*convert_to_string(long nb, int len, int sign);
int		get_size(int nb, int sign);

char	*ft_itoa(int nbr)
{
	long	nb;
	int		len;
	int		negative;

	nb = nbr;
	len = 0;
	negative = 0;
	if (nb < 0)
	{
		nb *= -1;
		negative = 1;
	}
	len = get_size(nbr, negative);
	return (convert_to_string(nb, len, negative));
}

int	get_size(int nb, int sign)
{
	int	len;
	int	n;

	n = nb;
	len = 0;
	if (n == 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	len = len + sign;
	return (len);
}

char	*convert_to_string(long nb, int len, int sign)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (len) + 1);
	if (str == NULL)
		return (NULL);
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len--] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
