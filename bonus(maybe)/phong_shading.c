/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_shading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:46:11 by ubazzane          #+#    #+#             */
/*   Updated: 2024/05/14 14:46:46 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* -----------------------------------------------------------------------
							Phong Model (specular)
------------------------------------------------------------------------- */
t_vec reflect(t_vec v, t_vec n) {
	return vec_sub(v, vec_scale(n, 2 * vec_dot(v, n)));
}

t_col	calc_phong_lighting(t_data *data, t_hit *obj, t_vec view_dir)
{
	t_vec	light_dir;
	double	ambient_ratio = 0.1;
	double	diffuse_ratio;
	double	specular_ratio;
	double	cos_angle;
	double	specular_exponent = 42.0; // Shininess factor
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
}
