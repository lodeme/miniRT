/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:50:46 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/11 16:00:33 by ubazzane         ###   ########.fr       */
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
	init_viewport(data);
	return (data);
}

void	init_viewport(t_data *data)
{
	data->cam->normal = vec_add(data->cam->normal, VEC_EPSILON);
	data->cam->normal = vec_norm(data->cam->normal);
	data->vp->vp_width = tan(RADIANS(data->cam->fov / 2.0));
	data->vp->vp_height = data->vp->vp_width / RATIO;
	data->vp->right_vec = vec_norm(vec_cross(data->cam->normal, VIEWPORT_UP));
	data->vp->up_vec = vec_norm(vec_cross(data->cam->normal, data->vp->right_vec));
	data->vp->right_vec = vec_norm(vec_cross(data->cam->normal, data->vp->up_vec));
}

/**
 * This function takes pixel coordinates as input and returns
 * the corresponding viewport coordinates, by scaling the input coordinates
 * from the range [0, WIDTH] or [0, HEIGHT] to the range [0, 2].
 * Subtracting 1 then shifts the range to [-1, 1].
 *
 * @param x: The x-coordinate in pixel coordinates.
 * @param y: The y-coordinate in pixel coordinates.

 * @return: A point representing the normalized viewport coordinates.
 */
t_vec	pixels_to_viewport(int x, int y)
{
	t_vec	pixel_location;

	pixel_location.x = ((2.0 * x) / WIDTH) - 1;
	pixel_location.y = ((2.0 * y) / HEIGHT) - 1;
	pixel_location.z = 0;
	return (pixel_location);
}
