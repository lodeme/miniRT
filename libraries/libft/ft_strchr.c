/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:18:54 by ubazzane          #+#    #+#             */
/*   Updated: 2023/11/25 15:24:24 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *string, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	if (!string)
		return (NULL);
	while (*string)
	{
		if (*string == uc)
			return ((char *)string);
		string++;
	}
	if (uc == '\0')
		return ((char *)string);
	return (NULL);
}
