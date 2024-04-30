/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:50:04 by ubazzane          #+#    #+#             */
/*   Updated: 2024/04/30 17:32:11 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	load_struct_cylinder(t_data *data, double *coordinates, double *normal,\
double *diameter, double *height, double *color, int index);

void	parse_sphere(t_data *data, char*** scene, int i)
{
	static int	index;
	double		*coordinates;
	double		*diameter;
	double		*color;

	if (ft_arrlen(scene[i]) != 4)
		throw_error(data, "Error: sphere must contain 3 parameters\n");
	if (!get_coordinates(&coordinates, scene, i))
		throw_error(data,"Error: (sphere) coordinates incorrect\n");
	if (!get_diameter(&diameter, scene, i, 2))
		throw_error(data, "Error: (sphere) diameter incorrect\n");
	if (!get_color(&color, scene, i, 3))
		throw_error(data, "Error: (sphere) color incorrect\n");
	data->spheres[index].center.x = coordinates[0];
	data->spheres[index].center.y = -1 * coordinates[1];
	data->spheres[index].center.z = coordinates[2];
	data->spheres[index].radius = *diameter / 2;
	data->spheres[index].color.r = color[0];
	data->spheres[index].color.g = color[1];
	data->spheres[index].color.b = color[2];
	index++;
	ft_free_multiple(3, coordinates, diameter, color);
}

void	parse_plane(t_data *data, char*** scene, int i)
{
	static int	index;
	double		*coordinates;
	double		*normal;
	double		*color;

	if (ft_arrlen(scene[i]) != 4)
		throw_error(data, "Error: plane must contain 3 parameters\n");
	if (!get_coordinates(&coordinates, scene, i))
		throw_error(data,"Error: (plane) coordinates incorrect\n");
	if (!get_normal(&normal, scene, i))
		throw_error(data, "Error: (plane) normal incorrect\n");
	if (!get_color(&color, scene, i, 3))
		throw_error(data, "Error: (plane) color incorrect\n");
	data->planes[index].center.x = coordinates[0];
	data->planes[index].center.y = -1 * coordinates[1];
	data->planes[index].center.z = coordinates[2];
	data->planes[index].normal.x = normal[0];
	data->planes[index].normal.y = -1 * normal[1]; //not sure this needs to be inverted
	data->planes[index].normal.z = normal[2];
	data->planes[index].color.r = color[0];
	data->planes[index].color.g = color[1];
	data->planes[index].color.b = color[2];
	index++;
	ft_free_multiple(3, coordinates, normal, color);
}

void	parse_cylinder(t_data *data, char*** scene, int i)
{
	static int	index;
	double		*coordinates;
	double		*normal;
	double		*diameter;
	double		*height;
	double		*color;

	if (ft_arrlen(scene[i]) != 6)
		throw_error(data, "Error: cylinder must contain 5 parameters\n");
	if (!get_coordinates(&coordinates, scene, i))
		throw_error(data,"Error: (cylinder) coordinates incorrect\n");
	if (!get_normal(&normal, scene, i))
		throw_error(data, "Error: (cylinder) normal incorrect\n");
	if (!get_diameter(&diameter, scene, i, 3))
		throw_error(data, "Error: (cylinder) diameter incorrect\n");
	if (!get_height(&height, scene, i))
		throw_error(data, "Error: (cylinder) height incorrect\n");
	if (!get_color(&color, scene, i, index))
		throw_error(data, "Error: (cylinder) color incorrect\n");
	load_struct_cylinder(data, coordinates, normal, diameter, height, color, index);
	index++;
	ft_free_multiple(5, coordinates, normal, diameter, height, color);
}

void	load_struct_cylinder(t_data *data, double *coordinates, double *normal,\
double *diameter, double *height, double *color, int index)
{
	data->cylinders[index].center.x = coordinates[0];
	data->cylinders[index].center.y = -1 * coordinates[1];
	data->cylinders[index].center.z = coordinates[2];
	data->cylinders[index].normal.x = normal[0];
	data->cylinders[index].normal.y = -1 * normal[1]; //not sure this needs to be inverted
	data->cylinders[index].normal.z = normal[2];
	data->cylinders[index].radius = *diameter / 2;
	data->cylinders[index].height = *height;
	data->cylinders[index].color.r = color[0];
	data->cylinders[index].color.g = color[1];
	data->cylinders[index].color.b = color[2];
}
