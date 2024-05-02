/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:55:03 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/02 18:03:12 by lodemetz         ###   ########.fr       */
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


t_col	pixel_color(t_data *data, t_ray *ray)
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
