/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:50:46 by lodemetz          #+#    #+#             */
/*   Updated: 2024/04/17 15:53:50 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	init_window(t_data *data)
{
	data->win = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (!data->win)
		throw_error(data);
	data->img = mlx_new_image(data->win, WIDTH, HEIGHT);
	if (!data->img || (mlx_image_to_window(data->win, data->img, 0, 0) < 0))
		throw_error(data);
}

void	init_scene(t_data *data)
{
	data->cam = malloc(sizeof(t_camera));
	if (!data->cam)
		throw_error(data);
	data->vp = malloc(sizeof(t_viewport));
	if (!data->vp)
		throw_error(data);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		throw_error(data);
	init_window(data);
	init_scene(data);
	return (data);
}
