/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:57:17 by lodemetz          #+#    #+#             */
/*   Updated: 2024/04/18 15:18:20 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	calc_color(t_col col)
{
	return ((col.r << 24) | (col.g << 16) | (col.b << 8) | col.a);
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
