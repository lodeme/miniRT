/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:29:19 by ubazzane          #+#    #+#             */
/*   Updated: 2024/04/25 12:48:56 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		if (ft_strcmp(scene[i][0], "A"))
			parse_ambient(data, scene, i);
		if (ft_strcmp(scene[i][0], "L"))
			parse_light(data, scene, i);
		if (ft_strcmp(scene[i][0], "C"))
			parse_camera(data, scene, i);
		if (ft_strcmp(scene[i][0], "sp"))
			parse_sphere(data, scene, i);
		if (ft_strcmp(scene[i][0], "pl"))
			parse_plane(data, scene, i);
		if (ft_strcmp(scene[i][0], "cy"))
			parse_cylinder(data, scene, i);
	}
	free_triple_pointer(scene);
}
