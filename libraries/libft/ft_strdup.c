/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:41:54 by ubazzane          #+#    #+#             */
/*   Updated: 2023/11/25 15:25:12 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*ptr;
	size_t	size;

	if (!src)
		return (NULL);
	size = ft_strlen(src) + 1;
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, src, size);
	return (ptr);
}
