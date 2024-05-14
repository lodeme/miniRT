/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:11:24 by ubazzane          #+#    #+#             */
/*   Updated: 2024/05/14 17:52:11 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	get_intensity(double *var, char ***scene, int arr_i, int str_i);
static int	get_fov(double *var, char ***scene, int arr_i);

void	parse_ambient(t_data *data, char ***scene, int i)
{
	t_light	ambient;

	if (ft_arrlen(scene[i]) != 3)
		throw_error(data, "Error: ambient must contain 2 parameters\n");
	if (!get_intensity(&ambient.ratio, scene, i, 1))
		throw_error(data, "Error: (ambient) intensity incorrect\n");
	if (!get_color(&ambient.color, scene, i, 2))
		throw_error(data, "Error: (ambient) color incorrect\n");
	data->ambient->color = ambient.color;
	data->ambient->ratio = ambient.ratio;
}

void	parse_light(t_data *data, char ***scene, int i)
{
	static int	index;
	t_light		light;

	if (ft_arrlen(scene[i]) != 4)
		throw_error(data, "Error: light must contain 3 parameters\n");
	if (!get_coordinates(&light.center, scene, i))
		throw_error(data, "Error: (light) coordinates incorrect\n");
	if (!get_intensity(&light.ratio, scene, i, 2))
		throw_error(data, "Error: (light) intensity incorrect\n");
	if (!get_color(&light.color, scene, i, 3))
		throw_error(data, "Error: (light) color incorrect\n");
	data->lights[index].center = light.center;
	data->lights[index].ratio = light.ratio;
	data->lights[index].color = light.color;
	data->nb_lights = index + 1;
	index++;
}

void	parse_camera(t_data *data, char ***scene, int i)
{
	static int	index;
	t_camera	cam;

	if (ft_arrlen(scene[i]) != 4)
		throw_error(data, "Error: camera must contain 3 parameters\n");
	if (!get_coordinates(&cam.center, scene, i))
		throw_error(data, "Error: (camera) coordinates incorrect\n");
	if (!get_normal(&cam.normal, scene, i))
		throw_error(data, "Error: (camera) normal incorrect\n");
	if (!get_fov(&cam.fov, scene, i))
		throw_error(data, "Error: (camera) fov incorrect\n");
	data->cam[index].center = cam.center;
	data->cam[index].normal = cam.normal;
	data->cam[index].fov = cam.fov;
	index++;
}

static int	get_fov(double *var, char ***scene, int arr_i)
{
	char	**temp;
	int		j;
	double	value;

	temp = ft_split(scene[arr_i][3], ',');
	if (!(temp))
		return (0);
	if (ft_arrlen(temp) != 1)
		return (free_double_pointer(temp), 0);
	j = -1;
	while (temp[++j])
	{
		if (!ft_is_float(temp[j]))
			return (free_double_pointer(temp), 0);
		value = ft_atoi(temp[j]);
		if (value < 0 || value > 180)
			return (free_double_pointer(temp), 0);
		*var = value;
	}
	free_double_pointer(temp);
	return (1);
}

static int	get_intensity(double *var, char ***scene, int arr_i, int str_i)
{
	char	**temp;
	int		j;
	double	value;

	temp = ft_split(scene[arr_i][str_i], ',');
	if (!(temp))
		return (0);
	if (ft_arrlen(temp) != 1)
		return (free_double_pointer(temp), 0);
	j = -1;
	while (temp[++j])
	{
		if (!ft_is_float(temp[j]))
			return (free_double_pointer(temp), 0);
		value = ft_atod(temp[j]);
		if (value < 0 || value > 1)
			return (free_double_pointer(temp), 0);
		var[j] = value;
	}
	free_double_pointer(temp);
	return (1);
}
