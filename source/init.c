/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:50:46 by lodemetz          #+#    #+#             */
/*   Updated: 2024/04/16 15:50:46 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_data *init_data(void)
{
  t_data *data;

  data = (t_data *)malloc(sizeof(t_data));
  if (!data)
    throw_error(data);
  data->win = mlx_init(WIDTH, HEIGHT, "miniRT", false);
  if (!data->win)
    throw_error(data);
  data->img = mlx_new_image(data->win, WIDTH, HEIGHT);
  if (!data->img || (mlx_image_to_window(data->win, data->img, 0, 0) < 0))
    throw_error(data);
  return (data);
}
