/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:52:15 by lodemetz          #+#    #+#             */
/*   Updated: 2024/01/26 17:02:54 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	throw_error(void)
{
	ft_putstr_fd("Error\n", 1);
	// free_env(env);
	exit(EXIT_FAILURE);
}

// void	hook(void *param)
// {
// 	t_env	*env;
//
// 	env = param;
// 	if (mlx_is_key_down(env->window, MLX_KEY_ESCAPE))
// 		mlx_close_window(env->window);
// 	if (mlx_is_key_down(env->window, MLX_KEY_UP))
// 		translate_y(env, 20);
// 	if (mlx_is_key_down(env->window, MLX_KEY_DOWN))
// 		translate_y(env, -20);
// 	if (mlx_is_key_down(env->window, MLX_KEY_RIGHT))
// 		translate_x(env, -20);
// 	if (mlx_is_key_down(env->window, MLX_KEY_LEFT))
// 		translate_x(env, 20);
// 	if (mlx_is_key_down(env->window, MLX_KEY_KP_ADD))
// 		zoom(env, 0.1);
// 	if (mlx_is_key_down(env->window, MLX_KEY_KP_SUBTRACT))
// 		zoom(env, -0.1);
// 	if (mlx_is_key_down(env->window, MLX_KEY_KP_8))
// 		rotate(env, 0.01);
// 	if (mlx_is_key_down(env->window, MLX_KEY_KP_2))
// 		rotate(env, -0.01);
// }

int minirt(mlx_image_t *img)
{
  int i;
  int j;
  int r;
  int g;
  int b;

  j = 0;
  while (j < HEIGHT)
  {
    i = 0;
    while (i < WIDTH)
    {
      r = (int)(255.999 * (double)(i) / (WIDTH - 1));
      g = (int)(255.999 * (double)(j) / (HEIGHT - 1));
      b = (int)(255.999 * 0.0);
      mlx_put_pixel(img, i, j, (r << 24) | (g << 16) | (b << 8) | 255);
      i++;
    }
    j++;
  }
  return (SUCCESS);
}

int	main(void)
{
	mlx_t		*window;
	mlx_image_t	*img;

  window = mlx_init(WIDTH, HEIGHT, "miniRT", false);
  if (!window)
    throw_error();
  img = mlx_new_image(window, WIDTH, HEIGHT);
  if (!img || (mlx_image_to_window(window, img, 0, 0) < 0))
    throw_error();
  if (minirt(img) != SUCCESS)
    return (EXIT_FAILURE);
  // mlx_loop_hook(window, hook, env);
  mlx_loop(window);
  // free_env(env);
	return (EXIT_SUCCESS);
}
