/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:52:15 by lodemetz          #+#    #+#             */
/*   Updated: 2024/04/30 12:21:00 by ubazzane         ###   ########.fr       */
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
	double	b;
	double	c;
	double	discriminant;

	oc = vec_sub(center, ray->origin);
	a = vec_dot(ray->direction, ray->direction);
	b = vec_dot(ray->direction, oc) * 2.0;
	c = vec_dot(oc, oc) - (radius * radius);
	discriminant = (b * b) - (a * c * 4);
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-b - sqrt(discriminant)) / (2.0 * a));
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
	cs2 = col_scale(new_col(0.4, 0.6, 1.0), a);
	cadd = col_add(cs1, cs2);
	return (cadd);
}

t_ray	create_ray(t_data *data, int x_index, int y_index)
{
	t_vec	pixel_center;
	t_vec	ray_direction;
	t_ray	ray;

	pixel_center = vec_add(vec_add(data->vp->pixel00_loc, \
				vec_scale(data->vp->pixel_dx, x_index)), \
				vec_scale(data->vp->pixel_dy, y_index));
	ray_direction = vec_sub(pixel_center, data->cam->center);
	ray = (t_ray){pixel_center, ray_direction};
	return (ray);
}

int	minirt(t_data *data)
{
	int		x_index;
	int		y_index;
	t_ray	ray;

	y_index = -1;
	while (++y_index < HEIGHT)
	{
		x_index = -1;
		while (++x_index < WIDTH)
		{
			ray = create_ray(data, x_index, y_index);
			mlx_put_pixel(data->img, x_index, y_index, calc_color(ray_color(data, &ray)));
		}
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

