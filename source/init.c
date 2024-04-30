/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:50:46 by lodemetz          #+#    #+#             */
/*   Updated: 2024/04/30 11:40:36 by ubazzane         ###   ########.fr       */
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
	double		vheight;
	double		vwidth;
	t_vec		viewport_upper_left;

	vheight = tan((data->cam->fov * M_PI / 180.0) / 2.0);
	vwidth = vheight * RATIO;
	data->vp->viewport_x = vec_norm(vec_cross(data->cam->normal, VIEWPORT_UP));
	data->vp->viewport_y = vec_norm(vec_cross(data->cam->normal, data->vp->viewport_x));
	data->vp->pixel_dx = vec_scale(data->vp->viewport_x, vwidth / WIDTH);
	data->vp->pixel_dy = vec_scale(data->vp->viewport_y, vheight / HEIGHT);
	viewport_upper_left = vec_sub(vec_sub(vec_sub(
					data->cam->center, vec_scale(data->cam->normal, FOCAL_LENGTH)), \
					vec_scale(data->vp->viewport_x, vwidth / 2.0)), \
					vec_scale(data->vp->viewport_y, vheight / 2.0));
	data->vp->pixel00_loc = vec_add(viewport_upper_left, \
		vec_scale(vec_add(data->vp->pixel_dx, data->vp->pixel_dy), 0.5));
}
