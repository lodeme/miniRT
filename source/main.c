/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:52:15 by lodemetz          #+#    #+#             */
/*   Updated: 2024/04/29 16:33:08 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>

// TODO : finish ray_color function
// TODO : create functions to calculate colors
// TODO : allocate memory where necessary
// TODO : test code

void	hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->win, MLX_KEY_ESCAPE))
		mlx_close_window(data->win);
}

double	hit_sphere(t_vec center, double radius, t_ray *ray)
{
	t_vec	oc;
	double	a;
	double	h;
	double	c;
	double	discriminant;

	oc = vec_sub(center, ray->origin);
	a = vec_length_squared(ray->direction);
	h = vec_dot(ray->direction, oc);
	c = vec_length_squared(oc) - (radius * radius);
	discriminant = (h * h) - (a * c);
	if (discriminant < 0.0)
		return (-1.0);
	else
		return ((-h - sqrt(discriminant)) / a);
}

t_col	ray_color(t_data *data, t_ray *ray)
{
	t_vec	unit_direction;
	double	a;
	t_col	cs1;
	t_col	cs2;
	t_col	cadd;
	double	t;
	t_vec	n;
	t_vec	c;

	t = hit_sphere(data->spheres[0].center, data->spheres[0].radius, ray);
	if (t > 0.0)
	{
		n = vec_norm(vec_sub(vec_at(t, ray), data->spheres[0].center));
		c = vec_scale(vec_add_const(n, 1), 0.5);
		return (new_col(c.x, c.y, c.z));
	}
	unit_direction = vec_norm(ray->direction);
	a = 0.5 * (unit_direction.y + 1.0);
	cs1 = col_scale(new_col(1.0, 1.0, 1.0), 1.0 - a);
	cs2 = col_scale(new_col(0.5, 0.7, 1.0), a);
	cadd = col_add(cs1, cs2);
	return (cadd);
}

void	calc_viewport(t_data *data)
{
	double		vheight;
	double		vwidth;
	t_vec		viewport_upper_left;

	vheight = tan((data->cam->fov * M_PI / 180.0) / 2.0);
	vwidth = vheight * RATIO;
	data->vp->viewport_x = vec_norm(vec_cross(VIEWPORT_UP, data->cam->normal));
	data->vp->viewport_y = vec_norm(vec_cross(data->vp->viewport_x, data->cam->normal));
	data->vp->pixel_dx = vec_scale(data->vp->viewport_x, vwidth / WIDTH);
	data->vp->pixel_dy = vec_scale(data->vp->viewport_y, vheight / HEIGHT);
	viewport_upper_left = vec_sub(vec_sub(vec_sub(
					data->cam->center, vec_scale(data->cam->normal, FOCAL_LENGTH)), \
					vec_scale(data->vp->viewport_x, vwidth / 2.0)), \
					vec_scale(data->vp->viewport_y, vheight / 2.0));
	data->vp->pixel00_loc = vec_add(viewport_upper_left, \
		vec_scale(vec_add(data->vp->pixel_dx, data->vp->pixel_dy), 0.5));
}

int	minirt(t_data *data)
{
	int		i;
	int		j;
	t_vec	pixel_center;
	t_vec	ray_direction;
	t_ray	ray;

	calc_viewport(data);
	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			pixel_center = vec_add(vec_add(data->vp->pixel00_loc, \
						vec_scale(data->vp->pixel_dx, i)), \
						vec_scale(data->vp->pixel_dy, j));
			ray_direction = vec_sub(pixel_center, data->cam->center);
			ray = (t_ray){pixel_center, ray_direction};
			mlx_put_pixel(data->img, i, j, calc_color(ray_color(data, &ray)));
			i++;
		}
		j++;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	char	***scene;

	if (argc == 2)
	{
		scene = extract_file_content(argv);
		data = init_data(scene);
		if (minirt(data) != SUCCESS)
			return (EXIT_FAILURE);
		mlx_loop_hook(data->win, hook, data);
		mlx_loop(data->win);
		free_data(data);
		return (EXIT_SUCCESS);
	}
	return (ft_putstr_fd("Error: invalid argument amount\n ", 2), 1);
}

