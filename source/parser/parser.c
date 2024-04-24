/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:29:19 by ubazzane          #+#    #+#             */
/*   Updated: 2024/04/24 17:43:52 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//TO DO:
//edit the free function
//add functions to header file
//create remaining parsing functions for other objects

char	***extract_file_content(char **argv)
{
	char ***file_content;

	check_file_extension(argv[1]);
	file_content = extract_content(argv[1]);
	return (file_content);
}

void	parse_scene(t_data *data, char*** scene)
{
	int	i;

	i = -1;
	while(scene[++i])
	{
		if (is_obj(scene[i][0]) == "sp")
			parse_sphere(data, scene, i);
		//parse_plane
		//parse_cylinder
		//parse_camera
		//parse_light
		//parse_ambient
	}
}

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
	if (!get_diameter(&diameter, scene, i))
		throw_error(data, "Error: (sphere) diameter incorrect\n");
	if (!get_color(&color, scene, i, index))
		throw_error(data, "Error: (sphere) color incorrect\n");
	data->spheres[index].center.x = coordinates[0];
	data->spheres[index].center.y = coordinates[1];
	data->spheres[index].center.z = coordinates[2];
	data->spheres[index].radius = *diameter / 2;
	data->spheres[index].color.r = color[0];
	data->spheres[index].color.g = color[1];
	data->spheres[index].color.b = color[2];
	index++;
}


