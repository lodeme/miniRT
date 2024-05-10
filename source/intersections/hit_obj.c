/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:26:06 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/10 15:28:37 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Whether the ray casted has touched the sphere
 *
 * @param center
 * @param radius
 * @param ray
 * @return if there is an intersection, return the t-value (length of
 * the ray from origin to intersection. Otherwise returns -1)
 */
/* double	hit_sphere(t_vec center, double radius, t_ray *ray)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec_sub(center, ray->origin);
	a = vec_dot(ray->direction, ray->direction);
	b = vec_dot(ray->direction, oc) * 2.0;
	c = vec_dot(oc, oc) - (radius * radius);
	discriminant = (b * b) - (a * c * 4);
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-b - sqrt(discriminant)) / (2.0 * a));
} */

double	hit_sphere(t_vec center, double radius, t_ray *ray)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t0;
	double	t1;

	oc = vec_sub(ray->origin, center);
	a = vec_dot(ray->direction, ray->direction);
	b = 2.0 * vec_dot(oc, ray->direction);
	c = vec_dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	else
	{
		t0 = (-b - sqrt(discriminant)) / (2.0 * a);
		t1 = (-b + sqrt(discriminant)) / (2.0 * a);
		if (t0 > 0)
			return t0;
		else if (t1 > 0)
			return t1;
		else
			return (-1.0);
	}
}

t_ray	create_ray(t_data *data, int x_index, int y_index)
{
	t_vec	pixel_center;
	t_vec	ray_direction;
	t_ray	ray;

	pixel_center = vec_add(vec_add(data->vp->pixel00_loc, \
				vec_scale(data->vp->pixel_dx, x_index)), \
				vec_scale(data->vp->pixel_dy, y_index));
	ray_direction = vec_norm(vec_sub(pixel_center, data->cam->center));
	ray = (t_ray){data->cam->center, ray_direction};
	return (ray);
}

