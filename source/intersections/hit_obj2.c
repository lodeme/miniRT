/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:22:52 by ubazzane          #+#    #+#             */
/*   Updated: 2024/05/13 22:32:01 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	verify_intersections(t_cylinder *cy, t_ray *ray,t_equation *equation, double *t, t_hit *closest);
static void		check_caps(t_cylinder *cy, t_vec cap, t_ray *ray, double eq_t, double *t, t_hit *closest);
static void		check_walls(t_cylinder *cy, t_ray *ray, double eq_t, double *t, t_hit *closest);
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
	verify_intersections(&cy, ray, &eq, &t, closest);
	if (t < 0.0f)
		return (-1);
	return (t);
}

static double	verify_intersections(t_cylinder *cy, t_ray *ray,t_equation *equation, double *t, t_hit *closest)
{
	double	t3;
	double	t4;

	t3 = cap_intersection(cy, ray, cy->cap1);
	t4 = cap_intersection(cy, ray, cy->cap2);
	*t = (double)INFINITY;
	check_walls(cy, ray, equation->t1, t, closest);
	check_walls(cy, ray, equation->t2, t, closest);
	check_caps(cy, cy->cap1, ray, t3, t, closest);
	check_caps(cy, cy->cap2, ray, t4, t, closest);
	if (*t == INFINITY)
		return (0);
	return (*t);
}

static void	check_caps(t_cylinder *cy, t_vec cap, t_ray *ray, double eq_t, double *t, t_hit *closest)
{
	double	len;
	t_vec	point;

	point = vec_at(eq_t, ray);
	len = vec_length(vec_sub(point, cap)) + EPSILON;
	if (len <= cy->radius && eq_t > EPSILON && eq_t < *t)
	{
		closest->cy_axis_point = cap;
		*t = eq_t;
	}
}

static void	check_walls(t_cylinder *cy, t_ray *ray, double eq_t, double *t, t_hit *closest)
{
	t_vec	point;
	t_vec	oc;
	t_vec	a;
	double	m;
	double	len;

	point = vec_at(eq_t, ray);
	oc = vec_sub(ray->origin, cy->cap1);
	m = vec_dot(ray->direction, cy->normal) * eq_t + \
		vec_dot(oc, cy->normal);
	a = vec_add(cy->cap1, vec_scale(cy->normal, m));
	len = vec_length(vec_sub(point, a)) - EPSILON;
	m -= EPSILON;
	if (m >= 0 && m <= cy->height && len <= cy->radius \
		&& eq_t > EPSILON && eq_t < *t)
		{
			*t = eq_t;
			closest->cy_axis_point = a;
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
