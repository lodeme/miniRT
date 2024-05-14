/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:50:04 by ubazzane          #+#    #+#             */
/*   Updated: 2024/05/14 18:40:34 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	load_struct_cylinder(t_data *data, t_cylinder *cy, int index);

void	parse_sphere(t_data *data, char ***scene, int i)
{
	static int	index;
	t_sphere	sphere;

	if (ft_arrlen(scene[i]) != 4)
		throw_error(data, "Error: sphere must contain 3 parameters\n");
	if (!get_coordinates(&sphere.center, scene, i))
		throw_error(data, "Error: (sphere) coordinates incorrect\n");
	if (!get_diameter(&sphere.radius, scene, i, 2))
		throw_error(data, "Error: (sphere) diameter incorrect\n");
	if (!get_color(&sphere.color, scene, i, 3))
		throw_error(data, "Error: (sphere) color incorrect\n");
	data->spheres[index].center = sphere.center;
	data->spheres[index].radius = sphere.radius / 2;
	data->spheres[index].color = sphere.color;
	data->nb_spheres = index + 1;
	index++;
}

void	parse_plane(t_data *data, char ***scene, int i)
{
	static int	index;
	t_plane		plane;

	if (ft_arrlen(scene[i]) != 4)
		throw_error(data, "Error: plane must contain 3 parameters\n");
	if (!get_coordinates(&plane.center, scene, i))
		throw_error(data, "Error: (plane) coordinates incorrect\n");
	if (!get_normal(&plane.normal, scene, i))
		throw_error(data, "Error: (plane) normal incorrect\n");
	if (!get_color(&plane.color, scene, i, 3))
		throw_error(data, "Error: (plane) color incorrect\n");
	data->planes[index].center = plane.center;
	data->planes[index].normal = vec_norm(plane.normal);
	data->planes[index].color = plane.color;
	data->nb_planes = index + 1;
	index++;
}

void	parse_cylinder(t_data *data, char ***scene, int i)
{
	static int	index;
	t_cylinder	cylinder;

	if (ft_arrlen(scene[i]) != 6)
		throw_error(data, "Error: cylinder must contain 5 parameters\n");
	if (!get_coordinates(&cylinder.center, scene, i))
		throw_error(data, "Error: (cylinder) coordinates incorrect\n");
	if (!get_normal(&cylinder.normal, scene, i))
		throw_error(data, "Error: (cylinder) normal incorrect\n");
	if (!get_diameter(&cylinder.radius, scene, i, 3))
		throw_error(data, "Error: (cylinder) diameter incorrect\n");
	if (!get_height(&cylinder.height, scene, i))
		throw_error(data, "Error: (cylinder) height incorrect\n");
	if (!get_color(&cylinder.color, scene, i, 5))
		throw_error(data, "Error: (cylinder) color incorrect\n");
	load_struct_cylinder(data, &cylinder, index);
	index++;
}

static void	load_struct_cylinder(t_data *data, t_cylinder *cy, int index)
{
	data->cylinders[index].center = cy->center;
	data->cylinders[index].normal = vec_norm(cy->normal);
	data->cylinders[index].radius = cy->radius / 2;
	data->cylinders[index].height = cy->height;
	data->cylinders[index].color = cy->color;
	data->cylinders[index].cap1 = vec_add(data->cylinders[index].center, \
	vec_scale(data->cylinders[index].normal, \
				-data->cylinders[index].height / 2));
	data->cylinders[index].cap2 = vec_add(data->cylinders[index].center, \
	vec_scale(data->cylinders[index].normal, \
				data->cylinders[index].height / 2));
	data->nb_cylinders = index + 1;
}
