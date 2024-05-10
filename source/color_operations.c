/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:57:17 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/10 15:37:19 by ubazzane         ###   ########.fr       */
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

t_col	col_mul(t_col v1, t_col v2)
{
	return (new_col(v1.r * v2.r, v1.g * v2.g, v1.b * v2.b));
}

t_col	clamp_color(t_col color)
{
	color.r = min(1.0, color.r);
	color.r = max(0.0, color.r);
	color.g = min(1.0, color.g);
	color.g = max(0.0, color.g);
	color.b = min(1.0, color.b);
	color.b = max(0.0, color.b);
	return (color);
}

double max(double a, double b)
{
	if (a > b)
		return a;
	return b;
}

double min(double a, double b)
{
	if (a < b)
		return a;
	return b;
}
