/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:58:41 by lodemetz          #+#    #+#             */
/*   Updated: 2024/04/17 15:54:26 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->win)
			free(data->win);
		if (data->img)
			free(data->img);
		free(data);
	}
}

void	throw_error(t_data *data)
{
	ft_putstr_fd("Error\n", 2);
	free_data(data);
	exit(EXIT_FAILURE);
}