/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:58:41 by lodemetz          #+#    #+#             */
/*   Updated: 2024/04/24 14:55:54 by ubazzane         ###   ########.fr       */
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
		if (data->cam)
			free(data->cam);
		if (data->vp)
			free(data->vp);
		free(data);
	}
}

void	throw_error(t_data *data, char *err)
{
	ft_putstr_fd(err, 2);
	free_data(data);
	exit(EXIT_FAILURE);
}
