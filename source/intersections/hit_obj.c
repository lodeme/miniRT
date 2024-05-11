/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:26:06 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/11 15:14:20 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_sphere(t_sphere sp, t_ray *ray)
{
	t_vec	oc;
	t_equation	eq;
	double	discriminant;

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
		if (eq.t1 > 0)
			return (eq.t1);
		else if (eq.t2 > 0)
			return (eq.t2);
		else
			return (-1.0);
	}
}

// t_ray	create_ray(t_data *data, int x_index, int y_index)
// {
// 	t_vec	pixel_center;
// 	t_vec	ray_direction;
// 	t_ray	ray;

// 	pixel_center = vec_add(vec_add(data->vp->pixel00_loc, \
// 				vec_scale(data->vp->pixel_dx, x_index)), \
// 				vec_scale(data->vp->pixel_dy, y_index));
// 	ray_direction = vec_sub(pixel_center, data->cam->center);
// 	ray = (t_ray){pixel_center, ray_direction};
// 	return (ray);
// }

t_ray	create_ray(t_data *data, t_vec factors)
{
	t_ray	ray;
	t_vec	vertical;
	t_vec	horizontal;
	t_vec	res;

	vertical = vec_scale(data->vp->up, factors.y * data->vp->hview);
	horizontal = vec_scale(data->vp->right, factors.x * data->vp->wview);
	res = vec_add(vertical, horizontal);
	res = vec_add(res, data->cam->normal);
	res = vec_add(res, data->cam->center);
	ray.origin = data->cam->center;
	ray.direction = vec_norm(vec_sub(res, ray.origin));
	return (ray);
}
