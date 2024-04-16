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

#include "fdf.h"

void	throw_error(t_env *env)
{
	ft_putstr_fd("Error\n", 1);
	free_env(env);
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

int	main(int argc, char **argv)
{
	mlx_t		*window;
	mlx_image_t	*img;
	t_env		*env;

	if (argc == 2 && WIDTH > 50 && HEIGHT > 50)
	{
		window = mlx_init(WIDTH, HEIGHT, "fdf", false);
		if (!window)
			throw_error(0);
		img = mlx_new_image(window, WIDTH, HEIGHT);
		if (!img || (mlx_image_to_window(window, img, 0, 0) < 0))
			throw_error(0);
		env = init_env(window, img);
		if (!env)
			throw_error(env);
		if (!load_map(env, argv[1]))
			throw_error(env);
		if (!plot_map(env))
			throw_error(env);
		mlx_loop_hook(window, hook, env);
		mlx_loop(window);
		free_env(env);
	}
	else
		throw_error(0);
	return (0);
}
