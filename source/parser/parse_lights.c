/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:11:24 by ubazzane          #+#    #+#             */
/*   Updated: 2024/04/30 12:00:40 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_intensity(double **var, char*** scene, int arr_i, int str_i);
int		get_fov(double **var, char*** scene, int arr_i);

void	parse_ambient(t_data *data, char*** scene, int i)
{
	double	*color;
	double	*intensity;

	if (ft_arrlen(scene[i]) != 3)
		throw_error(data, "Error: ambient must contain 2 parameters\n");
	if (!get_intensity(&intensity, scene, i, 1))
		throw_error(data, "Error: (ambient) intensity incorrect\n");
	if (!get_color(&color, scene, i, 2))
		throw_error(data, "Error: (ambient) color incorrect\n");
	data->ambient->color.r = color[0];
	data->ambient->color.g = color[1];
	data->ambient->color.b = color[2];
	data->ambient->ratio = *intensity;
	ft_free_multiple(2, color, intensity);
}

void	parse_light(t_data *data, char*** scene, int i)
{
	static int	index;
	double		*coordinates;
	double		*intensity;
	double		*color;

	if (ft_arrlen(scene[i]) != 4)
		throw_error(data, "Error: light must contain 3 parameters\n");
	if (!get_coordinates(&coordinates, scene, i))
		throw_error(data, "Error: (light) coordinates incorrect\n");
	if (!get_intensity(&intensity, scene, i, 2))
		throw_error(data, "Error: (light) intensity incorrect\n");
	if (!get_color(&color, scene, i, 3))
		throw_error(data, "Error: (light) color incorrect\n");
	data->lights[index].center.x = coordinates[0];
	data->lights[index].center.y = coordinates[1];
	data->lights[index].center.z = coordinates[2];
	data->lights[index].ratio = *intensity;
	data->lights[index].color.r = color[0];
	data->lights[index].color.g = color[1];
	data->lights[index].color.b = color[2];
	index++;
	ft_free_multiple(3, coordinates, intensity, color);
}

void	parse_camera(t_data *data, char*** scene, int i)
{
	static int	index;
	double		*coordinates;
	double		*normal;
	double		*fov;

	if (ft_arrlen(scene[i]) != 4)
		throw_error(data, "Error: camera must contain 3 parameters\n");
	if (!get_coordinates(&coordinates, scene, i))
		throw_error(data, "Error: (camera) coordinates incorrect\n");
	if (!get_normal(&normal, scene, i))
		throw_error(data, "Error: (camera) normal incorrect\n");
	if (!get_fov(&fov, scene, i))
		throw_error(data, "Error: (camera) fov incorrect\n");
	data->cam[index].center.x = coordinates[0];
	data->cam[index].center.y = coordinates[1];
	data->cam[index].center.z = coordinates[2];
	data->cam[index].normal.x = normal[0];
	data->cam[index].normal.y = normal[1];
	data->cam[index].normal.z = normal[2];
	data->cam[index].fov = *fov;
	index++;
	ft_free_multiple(3, coordinates, normal, fov);
}

int	get_fov(double **var, char*** scene, int arr_i)
{
	char	**temp;
	int		j;
	double	value;

	temp = ft_split(scene[arr_i][3], ',');
	if (ft_arrlen(temp) != 1)
		return (0);
	*var = malloc(sizeof(double));
	if (*var == NULL)
		return (0);
	j = -1;
	while (temp[++j])
	{
		if (!ft_is_float(temp[j]))
			return (free(*var), 0);
		value = ft_atoi(temp[j]);
		if (value < 0 || value > 180)
			return (free(*var), 0);
		**var = value;
	}
	return (1);
}

double	get_intensity(double **var, char*** scene, int arr_i, int str_i)
{
	char	**temp;
	int		j;
	double	value;

	temp = ft_split(scene[arr_i][str_i], ',');
	if (ft_arrlen(temp) != 1)
		return (0);
	*var = malloc(sizeof(double) * 3);
	if (*var == NULL)
		return (0);
	j = -1;
	while (temp[++j])
	{
		if (!ft_is_float(temp[j]))
			return (free(*var), 0);
		value = ft_atod(temp[j]);
		if (value < 0 || value > 1)
			return (free(*var), 0);
		(*var)[j] = value;
	}
	return (1);
}
