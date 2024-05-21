/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:42:57 by ubazzane          #+#    #+#             */
/*   Updated: 2024/05/14 16:43:12 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	vec_norm(t_vec v)
{
	return (vec_scale(v, 1.0 / vec_length(v)));
}

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
