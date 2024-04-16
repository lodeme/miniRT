/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane < ubazzane@student.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:59:19 by ubazzane          #+#    #+#             */
/*   Updated: 2023/11/14 12:13:20 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	size_t	little_len;

	if (little[0] == '\0')
		return ((char *)big);
	little_len = 0;
	while (little[little_len])
		little_len++;
	while (*big && len >= little_len)
	{
		i = 0;
		while ((little[i] == big[i]) && little[i])
			i++;
		if (little[i] == '\0')
			return ((char *)big);
		big ++;
		len--;
	}
	return (0);
}
