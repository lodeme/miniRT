/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:27:35 by ubazzane          #+#    #+#             */
/*   Updated: 2024/04/24 17:28:36 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int get_color(double **var, char*** scene, int arr_i, int str_i)
{
	char	**temp;
	int		j;
	double	color;

	temp = ft_split(scene[arr_i][str_i], ",");
	if (ft_arrlen(temp) != 3)
		return (0);
	*var = malloc(sizeof(double) * 3);
	if (*var == NULL)
		return (0);
	j = -1;
	while (temp[++j])
	{
		if(!ft_is_float(temp[j]))
			return (free(*var), 0);
		color = ft_atod(temp[j]);
		if (color < 0 || color > 255)
			return (free(*var), 0);
		(*var)[j] = color / 255.0;
	}
	return (1);
}

int	get_diameter(double **var, char*** scene, int arr_i)
{
	char	**temp;
	int		j;

	temp = ft_split(scene[arr_i][2], ",");
	if (ft_arrlen(temp) != 1)
		return (0);
	if (!ft_is_float(temp[0]))
		return (0);
	*var = malloc(sizeof(double));
	if (*var == NULL)
		return (0);
	**var = ft_atod(temp[0]);
	return (1);
}

int	get_coordinates(double **var, char*** scene, int arr_i)
{
	char	**temp;
	int		j;
	double	value;

	temp = ft_split(scene[arr_i][1], ",");
	if (ft_arrlen(temp) != 3)
		return (0);
	*var = malloc(sizeof(double) * 3);
	if (*var == NULL)
		return (0);
	j = -1;
	while (temp[++j])
	{
		if (!ft_is_float(temp[j]))
			return (free(*var), 0);
		(*var)[j] = ft_atod(temp[j]);
	}
	return (1);
}
