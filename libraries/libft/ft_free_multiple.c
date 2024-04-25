/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_multiple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:54:53 by ubazzane          #+#    #+#             */
/*   Updated: 2024/04/25 11:55:28 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	ft_free_multiple(int count, ...)
{
	va_list	args;
	void	*ptr;
	int		i;

	va_start(args, count);
	i = -1;
	while (++i < count)
	{
		ptr = va_arg(args, void *);
		if (ptr)
			free(ptr);
	}
	va_end(args);
}
