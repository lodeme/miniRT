/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane < ubazzane@student.42berlin.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:21:15 by ubazzane          #+#    #+#             */
/*   Updated: 2023/11/14 11:37:51 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	total_len;

	dest_len = 0;
	total_len = 0;
	while (dest_len < size && dest[dest_len])
		dest_len++;
	total_len = dest_len;
	while (src[total_len - dest_len] && total_len + 1 < size)
	{
		dest[total_len] = src[total_len - dest_len];
		total_len++;
	}
	if (total_len < size)
		dest[total_len] = '\0';
	while (src[total_len - dest_len])
		total_len++;
	return (total_len);
}
