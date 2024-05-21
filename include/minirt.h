/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodemetz <lodemetz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:26:29 by lodemetz          #+#    #+#             */
/*   Updated: 2024/05/21 12:46:59 by lodemetz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 1280
# define HEIGHT 720
# define RATIO 1.777777778
# define FOCAL_LENGTH 1
# define VIEWPORT_HEIGHT 2
# define PI 3.1415926535f
# define EPSILON 0.0001

# define SUCCESS 0
# define FAILURE 1

# include "libft.h"
# include "MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h>

typedef struct s_equation
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
}			t_equation;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_col
{
	double	r;
	double	g;
	double	b;
}	t_col;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}	t_ray;

typedef struct s_camera
{
	t_vec		center;
	t_vec		normal;
	double		fov;
}	t_camera;

typedef struct s_viewport
{
	t_vec	up_vec;
	t_vec	right_vec;
	double	vp_width;
	double	vp_height;
}	t_viewport;

typedef struct s_light
{
	t_vec	center;
	double	ratio;
	t_col	color;
}	t_light;

typedef struct s_sphere
{
	t_vec	center;
	double	radius;
	t_vec	normal;
	t_col	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec	center;
	t_vec	normal;
	t_col	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec	center;
	t_vec	cap1;
	t_vec	cap2;
	t_vec	normal;
	double	radius;
	double	height;
	t_col	color;
}	t_cylinder;

typedef struct s_data
{
	mlx_t		*win;
	mlx_image_t	*img;
	t_camera	*cam;
	t_viewport	*vp;
	t_light		*ambient;
	t_light		*lights;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
	int			nb_spheres;
	int			nb_planes;
	int			nb_cylinders;
	int			nb_lights;
}	t_data;

typedef struct s_hit
{
	char		*type;
	double		t;
	t_vec		hit_point;
	t_vec		normal;
	t_col		color;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_vec		cy_axis_point;
}	t_hit;

typedef struct s_calc_cy
{
	t_vec	axis_point;
	t_ray	*ray;
	double	t;
}	t_calc_cy;

// colors
int		convert_color(t_col col);
t_col	new_col(double r, double g, double b);
t_col	col_add(t_col v1, t_col v2);
t_col	col_scale(t_col v, double s);
t_col	col_mul(t_col v1, t_col v2);
t_col	clamp_color(t_col color);
double	max(double a, double b);
double	min(double a, double b);

// pixel operations
t_col	pixel_color(t_data *data, t_ray *ray, t_hit *obj);
bool	shadow(t_data *data, t_hit *obj);
void	put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);

// intersections
double	hit_sphere(t_sphere sp, t_ray *ray);
double	hit_plane(t_plane pl, t_ray *ray);
double	hit_cylinder(t_cylinder cy, t_ray *ray, t_hit *closest);
t_vec	cylinder_normal(t_hit *closest, t_ray *ray);
t_ray	create_ray(t_data *data, t_vec pixel);
t_hit	closest_obj(t_data *data, t_ray *ray);
t_vec	pixels_to_viewport(int x, int y);

// vector operations
t_vec	new_vec(double x, double y, double z);
t_vec	vec_add(t_vec v1, t_vec v2);
t_vec	vec_sub(t_vec v1, t_vec v2);
t_vec	vec_mult_vec(t_vec v1, t_vec v2);
t_vec	vec_scale(t_vec v, double s);
double	vec_length(t_vec v);
t_vec	vec_cross(t_vec v1, t_vec v2);
double	vec_dot(t_vec v1, t_vec v2);
t_vec	vec_norm(t_vec v);
//double	vec_div_num(t_vec v, double s);
t_vec	vec_at(double t, t_ray *ray);
t_vec	vec_add_const(t_vec v, double c);
double	vec_length_squared(t_vec v);
double	vec_cos(t_vec v1, t_vec v2);
bool	vec_compare(t_vec v1, t_vec v2);

// utils
t_data	*init_data(char ***scene);
void	free_data(t_data *data);
void	throw_error(t_data *data, char *err);
void	init_viewport(t_data *data);

// parser
char	***extract_file_content(char **argv);
void	parse_scene(t_data *data, char ***scene);
char	***extract_content(char *str);
void	parse_sphere(t_data *data, char ***scene, int i);
void	parse_plane(t_data *data, char ***scene, int i);
void	parse_cylinder(t_data *data, char ***scene, int i);
void	parse_camera(t_data *data, char ***scene, int i);
void	parse_light(t_data *data, char ***scene, int i);
void	parse_ambient(t_data *data, char ***scene, int i);
int		get_color(t_col *var, char ***scene, int arr_i, int str_i);
int		get_diameter(double *var, char ***scene, int arr_i, int str_i);
int		get_coordinates(t_vec *var, char ***scene, int arr_i);
int		get_normal(t_vec *var, char ***scene, int arr_i);
int		get_height(double *var, char ***scene, int arr_i);
void	quit_parsing(char *str);
void	check_file_extension(char *str);
char	*is_obj(char *str);
int		count_obj(char ***scene, char	*str);
void	check_objs(char ***content);

#endif
