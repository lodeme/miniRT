/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:48:09 by ubazzane          #+#    #+#             */
/*   Updated: 2024/05/14 16:49:11 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}
