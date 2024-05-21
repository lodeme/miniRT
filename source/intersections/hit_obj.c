/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:26:06 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/14 16:55:43 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_sphere(t_sphere sp, t_ray *ray)
{
	t_vec		oc;
	t_equation	eq;
	double		discriminant;

	oc = vec_sub(ray->origin, sp.center);
	eq.a = vec_dot(ray->direction, ray->direction);
	eq.b = 2.0 * vec_dot(oc, ray->direction);
	eq.c = vec_dot(oc, oc) - pow(sp.radius, 2);
	if (eq.a == 0.0 && eq.b != 0.0)
		return (-1.0);
	discriminant = pow(eq.b, 2) - 4 * eq.a * eq.c;
	if (discriminant < 0)
		return (-1.0);
	else
	{
		eq.t1 = (-eq.b - sqrt(discriminant)) / (2.0 * eq.a);
		eq.t2 = (-eq.b + sqrt(discriminant)) / (2.0 * eq.a);
		if (eq.t1 > EPSILON)
			return (eq.t1);
		else if (eq.t2 > EPSILON)
			return (eq.t2);
		else
			return (-1.0);
	}
}

double	hit_plane(t_plane pl, t_ray *ray)
{
	t_vec		oc;
	double		d_dot_v;
	double		x_dot_v;
	double		t;

	oc = vec_sub(ray->origin, pl.center);
	d_dot_v = vec_dot(ray->direction, pl.normal);
	x_dot_v = vec_dot(oc, pl.normal);
	if (d_dot_v != 0.0 && ((d_dot_v > 0 && x_dot_v < 0)
			|| (d_dot_v < 0 && x_dot_v > 0)))
	{
		t = -x_dot_v / d_dot_v;
		if (t > EPSILON)
			return (t);
	}
	return (-1.0);
}

t_ray	create_ray(t_data *data, t_vec pixel)
{
	t_ray	ray;
	t_vec	vertical;
	t_vec	horizontal;
	t_vec	unnormalized_direction;

	vertical = vec_scale(data->vp->up_vec, pixel.y * data->vp->vp_height);
	horizontal = vec_scale(data->vp->right_vec, pixel.x * data->vp->vp_width);
	unnormalized_direction = vec_add(vertical, horizontal);
	unnormalized_direction = vec_add(unnormalized_direction, data->cam->normal);
	unnormalized_direction = vec_add(unnormalized_direction, data->cam->center);
	ray.origin = data->cam->center;
	ray.direction = vec_norm(vec_sub(unnormalized_direction, ray.origin));
	return (ray);
}

t_vec	cylinder_normal(t_hit *closest, t_ray *ray)
{
	t_vec	point;
	t_vec	normal;

	point = vec_at(closest->t, ray);
	normal = vec_sub(point, closest->cy_axis_point);
	if (vec_compare(closest->cy_axis_point, closest->cylinder->cap1))
		normal = vec_scale(closest->cylinder->normal, -1);
	else if (vec_compare(closest->cy_axis_point, closest->cylinder->cap2))
		normal = closest->cylinder->normal;
	return (normal);
}
