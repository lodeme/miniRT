/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:26:06 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/10 16:34:42 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	determinant(t_equation *eq)
{
	double	delta;

	delta = pow(eq->b, 2) - (4 * eq->a * eq->c);
	if (delta < 0)
		return (-1);
	return (delta);
}

double	solve(t_equation *eq)
{
	double	delta;

	if (eq->a == 0.0 && eq->b != 0.0)
	{
		eq->t1 = -eq->c / eq->b;
		return (0);
	}
	else
	{
		delta = determinant(eq);
		if (delta < 0)
			return (-1);
		eq->t1 = (-eq->b - sqrt(delta)) / (2 * eq->a);
		eq->t2 = (-eq->b + sqrt(delta)) / (2 * eq->a);
		return (delta);
	}
}
double	hit_sphere(t_sphere sp, t_ray *ray)
{
	t_vec		co;
	t_equation	equation;

	equation.t1 = -1.0f;
	co = vec_sub(ray->origin, sp.center);
	equation.a = vec_dot(ray->direction, ray->direction);
	equation.b = 2.0f * vec_dot(co, ray->direction);
	equation.c = vec_dot(co, co) - pow(sp.radius, 2);
	if (solve(&equation) > 0 && \
		(equation.t1 > EPSILON || equation.t2 > EPSILON))
	{
		if (equation.t1 > EPSILON)
			return (equation.t1);
		else
			return (equation.t2);
	}
	return (-1);
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
