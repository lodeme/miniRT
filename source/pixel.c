/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:55:03 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/14 16:20:03 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_col	ambient(t_col object_color, t_col ambient_color, double ambient_ratio);
static t_col	calc_color(t_data *data, t_hit *obj);
static t_col	sky_gradient(t_ray *ray);
static t_col	calc_diffuse_light(t_data *scene_data, t_hit *obj);
bool	shadow(t_data *data, t_hit *obj);

t_col	pixel_color(t_data *data, t_ray *ray, t_hit *obj)
{
	if (obj->t > 0.0)
		return calc_color(data, obj);
	else
		//return ((t_col){0.0, 0.0, 0.0});
		return sky_gradient(ray);
}

static t_col	calc_color(t_data *data, t_hit *obj)
{
	t_col	color;

	color = ambient(obj->color, data->ambient->color, data->ambient->ratio);
	if (data->nb_lights > 0 && !shadow(data, obj))
		color = col_add(color, calc_diffuse_light(data, obj));
	color = clamp_color(color);
	return (color);
}

static	t_col	sky_gradient(t_ray *ray)
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

static t_col	calc_diffuse_light(t_data *scene_data, t_hit *obj)
{
	t_vec	light_direction;
	double	light_attenuation;
	double	angle_cosine;
	double	diffuse_light_intensity;
	t_col	diffuse_color;

	light_direction = vec_sub(scene_data->lights->center, obj->hit_point);
	light_attenuation = min(1.0, 90.0 / vec_length(light_direction));
	angle_cosine = vec_cos(obj->normal, light_direction);
	diffuse_light_intensity = scene_data->lights->ratio * angle_cosine * light_attenuation;
	diffuse_color = col_scale(obj->color, diffuse_light_intensity);
	return (diffuse_color);
}

static t_col	ambient(t_col object_color, t_col ambient_color, double ambient_ratio)
{
	return (col_scale(col_mul(object_color, ambient_color), ambient_ratio));
}

bool	shadow(t_data *data, t_hit *obj)
{
	t_ray	shadow_ray;
	t_hit	shadow_obj;
	int		i;

	i = -1;
	while (++i < data->nb_lights)
	{
		shadow_ray.origin = obj->hit_point;
		shadow_ray.direction = vec_norm(vec_sub(data->lights[i].center, obj->hit_point));
		shadow_obj = closest_obj(data, &shadow_ray);
		if (shadow_obj.t > 0.0 && shadow_obj.t < vec_length(vec_sub(data->lights[i].center, obj->hit_point)))
			return (true);
	}
	return (false);
}
