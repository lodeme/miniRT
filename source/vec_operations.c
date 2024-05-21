/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:45:38 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/14 16:42:23 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	new_vec(double x, double y, double z)
{
	return ((t_vec){x, y, z});
}

t_vec	vec_add(t_vec v1, t_vec v2)
{
	return (new_vec(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec	vec_add_const(t_vec v, double c)
{
	return (new_vec(v.x + c, v.y + c, v.z + c));
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	return (new_vec(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vec	vec_mult_vec(t_vec v1, t_vec v2)
{
	return (new_vec(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}
