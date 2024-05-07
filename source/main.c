/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:52:15 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/07 14:28:11 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>

void	hook(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->win, MLX_KEY_ESCAPE))
		mlx_close_window(data->win);
}

int	minirt(t_data *data)
{
	int		x_index;
	int		y_index;
	int		color;
	t_ray	ray;
	t_hit	obj;

	y_index = -1;
	while (++y_index < HEIGHT)
	{
		x_index = -1;
		while (++x_index < WIDTH)
		{
			ray = create_ray(data, x_index, y_index);
			obj = closest_obj(data, &ray);
			color = convert_color(pixel_color(data, &ray, &obj));
			mlx_put_pixel(data->img, x_index, y_index, color);
		}
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	char	***scene;

	if (argc == 2)
	{
		scene = extract_file_content(argv);
		data = init_data(scene);
		if (minirt(data) != SUCCESS)
			return (EXIT_FAILURE);
		mlx_loop_hook(data->win, hook, data);
		mlx_loop(data->win);
		free_data(data);
		return (EXIT_SUCCESS);
	}
	return (ft_putstr_fd("Error: invalid argument amount\n ", 2), 1);
}

