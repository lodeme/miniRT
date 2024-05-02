/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:57:17 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/02 18:24:06 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	convert_color(t_col col)
{
	int	r;
	int	g;
	int	b;

	r = (int)(col.r * 255.999);
	g = (int)(col.g * 255.999);
	b = (int)(col.b * 255.999);
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}
// color operations
t_col	new_col(double r, double g, double b)
{
	return ((t_col){r, g, b});
}

t_col	col_add(t_col v1, t_col v2)
{
	return (new_col(v1.r + v2.r, v1.g + v2.g, v1.b + v2.b));
}

t_col	col_scale(t_col v, double s)
{
	return (new_col(v.r * s, v.g * s, v.b * s));
}
