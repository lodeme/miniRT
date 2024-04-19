/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:52:15 by lodemetz          #+#    #+#             */
/*   Updated: 2024/04/18 16:40:18 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

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
	b = vec_dot(ray->direction, oc) * -2.0;
	c = vec_dot(oc, oc) - (radius * radius);
	discriminant = (b * b) - (a * c * 4);
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-b - sqrt(discriminant)) / (2.0 * a));
}

t_col	ray_color(t_ray *ray)
{
	t_vec	unit_direction;
	double	a;
	t_col	cs1;
	t_col	cs2;
	t_col	cadd;
	double	t;
	t_vec	n;
	t_vec	c;

	t = hit_sphere((t_vec){0, 0, -1.5}, 0.5, ray);
	if (t > 0.0)
	{
		printf("%f\n", t);
		n = vec_norm(vec_sub(vec_at(ray, t), new_vec(0, 0, -1)));
		c = vec_scale(new_vec(n.x + 1, n.y + 1, n.z + 1), 0.5);
		return (new_col(c.x, c.y, c.z, 1));
	}
	unit_direction = vec_norm(ray->direction);
	a = 0.5 * (unit_direction.y + 1.0);
	cs1 = col_scale(new_col(1.0, 1.0, 1.0, 1.0), 1.0 - a);
	cs2 = col_scale(new_col(0.5, 0.7, 1.0, 1.0), a);
	cadd = col_add(cs1, cs2);
	return (cadd);
}

void	calc_viewport(t_data *data)
{
	double		vheight;
	double		vwidth;
	t_vec		viewport_upper_left;

	vheight = 2.0;
	vwidth = vheight * ((double)WIDTH / HEIGHT);
	data->cam->center = (t_vec){0, 0, 0};
	data->vp->viewport_x = (t_vec){vwidth, 0, 0};
	data->vp->viewport_y = (t_vec){0, -vheight, 0};
	data->vp->pixel_dx = vec_scale(data->vp->viewport_x, 1.0 / WIDTH);
	data->vp->pixel_dy = vec_scale(data->vp->viewport_y, 1.0 / HEIGHT);
	viewport_upper_left = vec_sub(vec_sub(vec_sub(
					data->cam->center, (t_vec){0.0, 0.0, FOCAL_LENGTH}), \
					vec_scale(data->vp->viewport_x, 0.5)), \
					vec_scale(data->vp->viewport_y, 0.5));
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

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			calc_viewport(data);
			pixel_center = vec_add(vec_add(data->vp->pixel00_loc, \
						vec_scale(data->vp->pixel_dx, i)), \
						vec_scale(data->vp->pixel_dy, j));
			ray_direction = vec_sub(pixel_center, data->cam->center);
			ray = (t_ray){pixel_center, ray_direction};
			mlx_put_pixel(data->img, i, j, calc_color(ray_color(&ray)));
			i++;
		}
		j++;
	}
	return (SUCCESS);
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	if (minirt(data) != SUCCESS)
		return (EXIT_FAILURE);
	mlx_loop_hook(data->win, hook, data);
	mlx_loop(data->win);
	free_data(data);
	return (EXIT_SUCCESS);
}

