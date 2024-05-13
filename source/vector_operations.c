/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:45:38 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/13 22:17:34 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	new_vec(double x, double y, double z)
{
	return ((t_vec){x, y, z});
}

t_vec	vec_add(t_vec v1, t_vec v2)
{
	return (new_vec(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec	vec_add_const(t_vec v, double c)
{
	return (new_vec(v.x + c, v.y + c, v.z + c));
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	return (new_vec(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vec	vec_mult_vec(t_vec v1, t_vec v2)
{
	return (new_vec(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}

t_vec	vec_scale(t_vec v, double s)
{
	return (new_vec(v.x * s, v.y * s, v.z * s));
}

double	vec_length_squared(t_vec v)
{
	return (pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

double	vec_length(t_vec v)
{
	return (sqrt(vec_length_squared(v)));
}

t_vec	vec_cross(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}

double	vec_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	vec_norm(t_vec v)
{
	return (vec_scale(v, 1.0 / vec_length(v)));
}
/* double vec_div_num(t_vec v, double s)
{
	return ((v.x / s, v.y / s, v.z / s));
}hit_sphere((t_vec){0, 0, -1}, 0.5, ray) */

t_vec	vec_at(double t, t_ray *ray)
{
	return (vec_add(ray->origin, vec_scale(ray->direction, t)));
}
double	vec_cos(t_vec v1, t_vec v2)
{
	double	dot;
	double	lengths;

	dot = vec_dot(v1, v2);
	lengths = vec_length(v1) * vec_length(v2);
	return (dot / lengths);
}

bool	vec_compare(t_vec v1, t_vec v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}
