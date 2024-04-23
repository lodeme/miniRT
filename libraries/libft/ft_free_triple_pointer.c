/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_triple_pointer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:43:51 by ubazzane          #+#    #+#             */
/*   Updated: 2024/04/23 14:44:36 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_triple_pointer(char ***arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free_double_pointer(arr[i++]);
	free(arr);
}
