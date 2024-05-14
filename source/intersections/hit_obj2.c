/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:22:52 by ubazzane          #+#    #+#             */
/*   Updated: 2024/05/14 19:22:22 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	verify_intersections(t_cylinder *cy, t_ray *ray, \
							t_equation *equation, t_hit *closest);
static void		check_caps(t_cylinder *cy, t_vec cap, \
							double eq_t, t_calc_cy *hit);
static void		check_walls(t_cylinder *cy, double eq_t, t_calc_cy *hit);
static double	cap_intersection(t_cylinder *cy, t_ray *ray, t_vec cap);

double	hit_cylinder(t_cylinder cy, t_ray *ray, t_hit *closest)
{
	double		t;
	t_vec		oc;
	t_equation	eq;
	double		discriminant;

	oc = vec_sub(ray->origin, cy.cap1);
	eq.a = vec_dot(ray->direction, ray->direction) - \
		pow(vec_dot(ray->direction, cy.normal), 2);
	eq.b = 2 * (vec_dot(ray->direction, oc) - \
		(vec_dot(ray->direction, cy.normal) * vec_dot(oc, cy.normal)));
	eq.c = vec_dot(oc, oc) - pow(vec_dot(oc, cy.normal), 2) - \
		pow(cy.radius, 2);
	if (eq.a == 0.0 && eq.b != 0.0)
		eq.t1 = -eq.c / eq.b;
	discriminant = pow(eq.b, 2) - (4 * eq.a * eq.c);
	if (discriminant < 0)
		return (-1);
	eq.t1 = (-eq.b - sqrt(discriminant)) / (2 * eq.a);
	eq.t2 = (-eq.b + sqrt(discriminant)) / (2 * eq.a);
	if (eq.t1 <= 0 && eq.t2 <= 0)
		return (-1);
	t = verify_intersections(&cy, ray, &eq, closest);
	if (t < 0.0f)
		return (-1);
	return (t);
}

static double	verify_intersections(t_cylinder *cy, t_ray *ray, \
							t_equation *equation, t_hit *closest)
{
	double		t3;
	double		t4;
	t_calc_cy	hit;

	t3 = cap_intersection(cy, ray, cy->cap1);
	t4 = cap_intersection(cy, ray, cy->cap2);
	hit.t = (double)INFINITY;
	hit.ray = ray;
	check_walls(cy, equation->t1, &hit);
	check_walls(cy, equation->t2, &hit);
	check_caps(cy, cy->cap1, t3, &hit);
	check_caps(cy, cy->cap2, t4, &hit);
	closest->cy_axis_point = hit.axis_point;
	if (hit.t == INFINITY)
		return (-1);
	return (hit.t);
}

static void	check_caps(t_cylinder *cy, t_vec cap, double eq_t, t_calc_cy *hit)
{
	double	len;
	t_vec	point;

	point = vec_at(eq_t, hit->ray);
	len = vec_length(vec_sub(point, cap)) + EPSILON;
	if (len <= cy->radius && eq_t > EPSILON && eq_t < hit->t)
	{
		hit->axis_point = cap;
		hit->t = eq_t;
	}
}

static void	check_walls(t_cylinder *cy, double eq_t, t_calc_cy *hit)
{
	t_vec	point;
	t_vec	oc;
	t_vec	a;
	double	m;
	double	len;

	point = vec_at(eq_t, hit->ray);
	oc = vec_sub(hit->ray->origin, cy->cap1);
	m = vec_dot(hit->ray->direction, cy->normal) * eq_t + \
		vec_dot(oc, cy->normal);
	a = vec_add(cy->cap1, vec_scale(cy->normal, m));
	len = vec_length(vec_sub(point, a)) - EPSILON;
	m -= EPSILON;
	if (m >= 0 && m <= cy->height && len <= cy->radius \
		&& eq_t > EPSILON && eq_t < hit->t)
	{
		hit->t = eq_t;
		hit->axis_point = a;
	}
}

static double	cap_intersection(t_cylinder *cy, t_ray *ray, t_vec cap)
{
	t_plane	plane;

	plane.center = cap;
	plane.normal = cy->normal;
	plane.color = (t_col){0, 0, 0};
	return (hit_plane(plane, ray));
}
