/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:55:03 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/03 16:27:29 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col	sky_gradient(t_ray *ray)
{
	t_vec	unit_direction;
	double	a;
	t_col	cs1;
	t_col	cs2;
	t_col	cadd;

	unit_direction = vec_norm(ray->direction);
	a = 0.5 * (unit_direction.y + 1.0);
	cs1 = col_scale(new_col(1.0, 1.0, 1.0), 1.0 - a);
	cs2 = col_scale(new_col(0.4, 0.6, 1.0), a);
	cadd = col_add(cs1, cs2);
	return (cadd);
}

double max(double a, double b)
{
	if (a > b)
		return a;
	return b;
}

t_col	calc_diffuse_light(t_data *data, t_vec hit_point, t_vec normal)
{
	t_vec	light_dir;
	double	lambertian;
	t_col	light_color;
	t_col	object_color;

	light_dir = vec_norm(vec_sub(data->lights->center, hit_point));
	lambertian = max(0.0, vec_dot(normal, light_dir));
	light_color = data->lights->color;
	object_color = data->spheres[0].color;
	return col_scale(col_mul(object_color, light_color), lambertian);
}

t_col	pixel_color(t_data *data, t_ray *ray)
{
	double	t;
	t_vec	hit_point;
	t_vec	normal;

	t = hit_sphere(data->spheres[0].center, data->spheres[0].radius, ray);
	if (t > 0.0)
	{
		hit_point = vec_add(ray->origin, vec_scale(ray->direction, t));
		normal = vec_norm(vec_sub(hit_point, data->spheres[0].center));
		return calc_diffuse_light(data, hit_point, normal);
	}
	else
		return sky_gradient(ray);
}

/* t_col	pixel_color(t_data *data, t_ray *ray)
{
	double	t;

	t = hit_sphere(data->spheres[0].center, data->spheres[0].radius, ray);
	if (t > 0.0)
	{
		// calc_diffuse_color()
		// add_ambient_and_diffuse_lights()
		return (data->spheres[0].color);
	}
	else
		return(sky_gradient(ray));
}

t_col ambient(t_data *data)
{
	return (col_scale(data->ambient->color, data->ambient->ratio));
} */
