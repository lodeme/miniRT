/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:58:41 by lodemetz          #+#    #+#             */
/*   Updated: 2024/04/16 15:58:41 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void free_data(t_data *data)
{
  if (data)
  {
    if (data->win)
      free(data->win);
    if (data->img)
      free(data->img);
    free(data);
  }
}

void	throw_error(t_data *data)
{
	ft_putstr_fd("Error\n", 2);
  free_data(data);
  exit(EXIT_FAILURE);
}

