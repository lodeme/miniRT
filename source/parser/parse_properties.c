/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:27:35 by ubazzane          #+#    #+#             */
/*   Updated: 2024/05/14 17:04:56 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color(double **var, char ***scene, int arr_i, int str_i)
{
	char	**temp;
	int		j;
	double	color;

	temp = ft_split(scene[arr_i][str_i], ',');
	if (!(temp))
		return (0);
	if (ft_arrlen(temp) != 3)
		return (free_double_pointer(temp), 0);
	*var = malloc(sizeof(double) * 3);
	if (*var == NULL)
		return (free_double_pointer(temp), 0);
	j = -1;
	while (temp[++j])
	{
		if (!ft_is_float(temp[j]))
			return (free(*var), free_double_pointer(temp), 0);
		color = ft_atod(temp[j]);
		if (color < 0 || color > 255)
			return (free(*var), free_double_pointer(temp), 0);
		(*var)[j] = color / 255.0;
	}
	free_double_pointer(temp);
	return (1);
}

int	get_diameter(double **var, char ***scene, int arr_i, int str_i)
{
	char	**temp;

	temp = ft_split(scene[arr_i][str_i], ',');
	if (!(temp))
		return (0);
	if (ft_arrlen(temp) != 1)
		return (free_double_pointer(temp), 0);
	if (!ft_is_float(temp[0]))
		return (free_double_pointer(temp), 0);
	*var = malloc(sizeof(double));
	if (*var == NULL)
		return (free_double_pointer(temp), 0);
	**var = ft_atod(temp[0]);
	free_double_pointer(temp);
	return (1);
}

int	get_coordinates(double **var, char ***scene, int arr_i)
{
	char	**temp;
	int		j;

	temp = ft_split(scene[arr_i][1], ',');
	if (!(temp))
		return (0);
	if (ft_arrlen(temp) != 3)
		return (free_double_pointer(temp), 0);
	*var = malloc(sizeof(double) * 3);
	if (*var == NULL)
		return (free_double_pointer(temp), 0);
	j = -1;
	while (temp[++j])
	{
		if (!ft_is_float(temp[j]))
			return (free(*var), free_double_pointer(temp), 0);
		(*var)[j] = ft_atod(temp[j]);
	}
	free_double_pointer(temp);
	return (1);
}

int	get_normal(double **var, char ***scene, int arr_i)
{
	char	**temp;
	int		j;
	double	value;

	temp = ft_split(scene[arr_i][2], ',');
	if (!(temp))
		return (0);
	if (ft_arrlen(temp) != 3)
		return (free_double_pointer(temp), 0);
	*var = malloc(sizeof(double) * 3);
	if (*var == NULL)
		return (free_double_pointer(temp), 0);
	j = -1;
	while (temp[++j])
	{
		if (!ft_is_float(temp[j]))
			return (free(*var), free_double_pointer(temp), 0);
		value = ft_atod(temp[j]);
		if (value < -1 || value > 1)
			return (free(*var), free_double_pointer(temp), 0);
		(*var)[j] = value;
	}
	free_double_pointer(temp);
	return (1);
}

int	get_height(double **var, char ***scene, int arr_i)
{
	char	**temp;

	temp = ft_split(scene[arr_i][4], ',');
	if (!(temp))
		return (0);
	if (ft_arrlen(temp) != 1)
		return (free_double_pointer(temp), 0);
	if (!ft_is_float(temp[0]))
		return (free_double_pointer(temp), 0);
	*var = malloc(sizeof(double));
	if (*var == NULL)
		return (free_double_pointer(temp), 0);
	**var = ft_atod(temp[0]);
	free_double_pointer(temp);
	return (1);
}
