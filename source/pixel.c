/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:55:03 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/11 17:14:12 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col	ambient(t_col object_color, t_col ambient_color, double ambient_ratio);
t_col	clamp_color(t_col color);

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

/* --------------------------------------------------------------------------
						Our shading vesion (IT IS WORKING)
-----------------------------------------------------------------------------*/

/* t_col	calc_diffuse_light(t_data *data, t_hit *obj)
{
	t_vec	light_dir;
	double	lambertian;
	t_col	light_color;

	light_dir = vec_norm(vec_sub(data->lights->center, obj->hit_point));
	lambertian = max(0.0, vec_dot(obj->normal, light_dir));
	light_color = data->lights->color;
	return (col_scale(col_mul(obj->color, light_color), lambertian));
}*/

/* --------------------------------------------------------------------------
						Nuno's shading version
-----------------------------------------------------------------------------*/

t_col	calc_diffuse_light(t_data *data, t_hit *obj)
{
	t_vec	light_dir;
	double	attenuation;
	double	cos_angle;
	double	diffuse_ratio;
	t_col	diff_color;

	light_dir = vec_sub(data->lights->center, obj->hit_point);
	attenuation = min(1.0, 90.0 / vec_length(light_dir));
	cos_angle = vec_cos(obj->normal, light_dir);
	diffuse_ratio = data->lights->ratio * cos_angle * attenuation;
	diff_color = col_scale(obj->color, diffuse_ratio);
	return (diff_color);
}
/* ------------------------- Main Code -------------------------------- */

t_col calc_test(t_data *data, t_hit *obj)
{
	t_col	color;

	color = ambient(obj->color, data->ambient->color, data->ambient->ratio);
	color = col_add(color, calc_diffuse_light(data, obj));
	color = clamp_color(color);
	return color;
}

t_col	pixel_color(t_data *data, t_ray *ray, t_hit *obj)
{
	if (obj->t > 0.0)
		return calc_test(data, obj);
	else
		//return ((t_col){0.0, 0.0, 0.0});
		return sky_gradient(ray);
}

t_col	ambient(t_col object_color, t_col ambient_color, double ambient_ratio)
{
	return (col_scale(col_mul(object_color, ambient_color), ambient_ratio));
}

/* -----------------------------------------------------------------------
							Phong Model (specular)
------------------------------------------------------------------------- */
/* t_vec reflect(t_vec v, t_vec n) {
	return vec_sub(v, vec_scale(n, 2 * vec_dot(v, n)));
}

t_col	calc_phong_lighting(t_data *data, t_hit *obj, t_vec view_dir)
{
	t_vec	light_dir;
	double	ambient_ratio = 0.1;
	double	diffuse_ratio;
	double	specular_ratio;
	double	cos_angle;
	double	specular_exponent = 32.0; // Shininess factor
	t_col	ambient_color;
	t_col	diffuse_color;
	t_col	specular_color;
	t_col	final_color;

	// Calculate light direction
	light_dir = vec_norm(vec_sub(data->lights->center, obj->hit_point));

	// Ambient
	ambient_color = col_scale(obj->color, ambient_ratio);

	// Diffuse
	cos_angle = max(0.0, vec_dot(obj->normal, light_dir));
	diffuse_ratio = data->lights->ratio * cos_angle;
	diffuse_color = col_scale(col_mul(obj->color, data->lights->color), diffuse_ratio);

	// Specular
	t_vec reflect_dir = reflect(vec_scale(light_dir, -1), obj->normal);
	double spec = pow(max(0.0, vec_dot(view_dir, reflect_dir)), specular_exponent);
	specular_ratio = data->lights->ratio * spec;
	specular_color = col_scale(data->lights->color, specular_ratio);

	// Combine all components
	final_color = col_add(ambient_color, diffuse_color);
	final_color = col_add(final_color, specular_color);

	return (final_color);
}

t_col	calc_test(t_data *data, t_hit *obj, t_vec view_dir)
{
	t_col	color;

	color = ambient(obj->color, data->ambient->color, data->ambient->ratio);
	color = col_add(color, calc_phong_lighting(data, obj, view_dir));
	color = clamp_color(color);
	return (color);
}

t_col	pixel_color(t_data *data, t_ray *ray, t_hit *obj)
{
	if (obj->t > 0.0)
		return (calc_test(data, obj, vec_scale(ray->direction, -1)));
	else
		//return ((t_col){0.0, 0.0, 0.0});
		return (sky_gradient(ray));
}

t_col	ambient(t_col object_color, t_col ambient_color, double ambient_ratio)
{
	return (col_scale(col_mul(object_color, ambient_color), ambient_ratio));
} */
