/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:36:21 by ubazzane          #+#    #+#             */
/*   Updated: 2024/05/14 16:37:46 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	shadow(t_data *data, t_hit *obj)
{
	t_ray	shadow_ray;
	t_hit	shadow_obj;
	int		i;

	i = -1;
	while (++i < data->nb_lights)
	{
		shadow_ray.origin = obj->hit_point;
		shadow_ray.direction = vec_norm(vec_sub(data->lights[i].center, \
										obj->hit_point));
		shadow_obj = closest_obj(data, &shadow_ray);
		if (shadow_obj.t > 0.0 && shadow_obj.t < vec_length(\
			vec_sub(data->lights[i].center, obj->hit_point)))
			return (true);
	}
	return (false);
}
