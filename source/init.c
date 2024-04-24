/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:50:46 by lodemetz          #+#    #+#             */
/*   Updated: 2024/04/24 15:08:05 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	init_window(t_data *data)
{
	data->win = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (!data->win)
		throw_error(data, "Error: mlx_init() fail\n");
	data->img = mlx_new_image(data->win, WIDTH, HEIGHT);
	if (!data->img || (mlx_image_to_window(data->win, data->img, 0, 0) < 0))
		throw_error(data, "Error: img_init fail\n");
}

void	init_scene(t_data *data, char ***scene)
{
	data->cam = malloc(sizeof(t_camera));
	if (!data->cam)
		throw_error(data, "Error: malloc() fail\n");
	data->vp = malloc(sizeof(t_viewport));
	if (!data->vp)
		throw_error(data, "Error: malloc() fail\n");
	data->ambient = malloc(sizeof(t_light));
	if (!data->ambient)
		throw_error(data, "Error: malloc() fail\n");
	data->lights = malloc(sizeof(t_light) * count_obj(scene, "L"));
	if (!data->lights)
		throw_error(data, "Error: malloc() fail\n");
	data->spheres = malloc(sizeof(t_sphere) * count_obj(scene, "sp"));
	if (!data->spheres)
		throw_error(data, "Error: malloc() fail\n");
	data->planes = malloc(sizeof(t_plane) * count_obj(scene, "pl"));
	if (!data->planes)
		throw_error(data, "Error: malloc() fail\n");
	data->cylinders = malloc(sizeof(t_cylinder) * count_obj(scene, "cy"));
	if (!data->cylinders)
		throw_error(data, "Error: malloc() fail\n");
}

t_data	*init_data(char ***scene)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		throw_error(data, "Error: malloc() fail\n");
	init_window(data);
	init_scene(data, scene);
	parse_scene(data, scene);
	return (data);
}
