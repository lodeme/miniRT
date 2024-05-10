/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:21:15 by ubazzane          #+#    #+#             */
/*   Updated: 2024/05/10 16:32:35 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	get_closest_sphere(t_data *data, t_ray *ray, t_hit *closest);
//static void	get_closest_plane(t_data *data, t_ray *ray, t_hit *closest);
//static void	get_closest_cylinder(t_data *data, t_ray *ray, t_hit *closest);
static void	get_the_closest(t_ray *ray, t_hit *closest);

t_hit	closest_obj(t_data *data, t_ray *ray)
{
	t_hit	closest;

	closest.t = INFINITY;
	get_closest_sphere(data, ray, &closest);
	/* get_closest_plane(data, ray, &closest);
	get_closest_cylinder(data, ray, &closest); */
	get_the_closest(ray, &closest);
	return (closest);
}

static void	get_closest_sphere(t_data *data, t_ray *ray, t_hit *closest)
{
	int		i;
	double	t;

	i = -1;
	while (++i < data->nb_spheres)
	{
		t = hit_sphere(data->spheres[i], ray);
		if (t != -1 && t < closest->t)
		{
			closest->t = t;
			closest->type = "sphere";
			closest->sphere = &data->spheres[i];
		}
	}
}

/* static void	get_closest_plane(t_data *data, t_ray *ray, t_hit *closest)
{
	int		i;
	double	t;

	i = -1;
	while (++i < data->nb_planes)
	{
		t = hit_plane(data->planes[i].center, data->planes[i].normal, ray);
		if (t < closest->t)
		{
			closest->t = t;
			closest->type = "plane";
			closest->plane = &data->planes[i];
		}
	}
} */

/* static void	get_closest_cylinder(t_data *data, t_ray *ray, t_hit *closest)
{
	int		i;
	double	t;

	i = -1;
	while (++i < data->nb_cylinders)
	{
		t = hit_cylinder(data->cylinders[i].center, data->cylinders[i].normal,\
			 data->cylinders[i].radius, data->cylinders[i].height, ray);
		if (t < closest->t)
		{
			closest->t = t;
			closest->type = "cylinder";
			closest->cylinder = &data->cylinders[i];
		}
	}
} */

static void	get_the_closest(t_ray *ray, t_hit *closest)
{
	if (closest->t == INFINITY)
	{
		closest->type = "none";
		closest->t = -1;
	}
	closest->hit_point = vec_add(ray->origin, vec_scale(ray->direction, closest->t));
	if (!ft_strcmp(closest->type, "sphere"))
	{
		closest->normal = vec_norm(vec_sub(closest->hit_point, closest->sphere->center));
		closest->color = closest->sphere->color;
	}
/* 	else if (!ft_strcmp(closest->type, "plane"))
	{
		closest->normal = closest->plane->normal;
		closest->color = closest->plane->color;
	}
	else if (!ft_strcmp(closest->type, "cylinder"))
	{
		closest->normal = vec_norm(vec_sub(closest->hit_point, closest->cylinder->center));
		closest->color = closest->cylinder->color;
	} */
}
