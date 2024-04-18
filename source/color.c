/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:57:17 by lodemetz          #+#    #+#             */
/*   Updated: 2024/04/18 16:37:49 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	calc_color(t_col col)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = (int)(col.r * 255.999);
	g = (int)(col.g * 255.999);
	b = (int)(col.b * 255.999);
	a = (int)(col.a * 255.999);
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
// color operations
t_col	new_col(double r, double g, double b, double a)
{
	return ((t_col){r, g, b, a});
}

t_col	col_add(t_col v1, t_col v2)
{
	return (new_col(v1.r + v2.r, v1.g + v2.g, v1.b + v2.b, v1.a + v2.a));
}

t_col	col_scale(t_col v, double s)
{
	return (new_col(v.r * s, v.g * s, v.b * s, v.a * s));
}
