/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:52:15 by lodemetz          #+#    #+#             */
/*   Updated: 2024/04/17 15:54:53 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hook(void *param)
{
	t_data *data;

	data = param;
	if (mlx_is_key_down(data->win, MLX_KEY_ESCAPE))
		mlx_close_window(data->win);
}

int	minirt(t_data *data)
{
	int	i;
	int	j;
	int	r;
	int	g;
	int	b;

	j = 0;
	while (j < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			r = (int)(255.999 * (double)(i) / (WIDTH - 1));
			g = (int)(255.999 * (double)(j) / (HEIGHT - 1));
			b = (int)(255.999 * 0.0);
			mlx_put_pixel(data->img, i, j, calc_color(r, g, b, 255));
			i++;
		}
		j++;
	}
	return (SUCCESS);
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	if (minirt(data) != SUCCESS)
		return (EXIT_FAILURE);
	mlx_loop_hook(data->win, hook, data);
	mlx_loop(data->win);
	free_data(data);
	return (EXIT_SUCCESS);
}
