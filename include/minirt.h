
#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 1280
# define HEIGHT 720
# define RATIO 1.777777778
# define FOCAL_LENGTH 1
# define VIEWPORT_HEIGHT 2

# define SUCCESS 0
# define FAILURE 1

# include "libft.h"
# include "MLX42/MLX42.h"
# include <math.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_col
{
	int	r;
	int	g;
	int	b;
	int	a;
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
	t_vec	viewport_x;
	t_vec	viewport_y;
	t_vec	pixel_dx;
	t_vec	pixel_dy;
	t_vec	pixel00_loc;
}	t_viewport;

typedef struct s_sphere
{
	t_vec	center;
	t_vec	normal;
	t_col	color;
}	t_sphere;

typedef struct s_data
{
	mlx_t				*win;
	mlx_image_t	*img;
	t_camera		*cam;
	t_viewport	*vp;
}	t_data;

// colors
int		calc_color(t_col col);
t_col	new_col(double r, double g, double b, double a);
t_col	col_add(t_col v1, t_col v2);
t_col	col_scale(t_col v, double s);

// vector operations
t_vec new_vec(double x, double y, double z);
t_vec vec_add(t_vec v1, t_vec v2);
t_vec vec_sub(t_vec v1, t_vec v2);
t_vec vec_mult_vec(t_vec v1, t_vec v2);
t_vec vec_scale(t_vec v, double s);
double vec_length(t_vec v);
t_vec vec_cross(t_vec v1, t_vec v2);
double vec_dot(t_vec v1, t_vec v2);
t_vec vec_norm(t_vec v);
double vec_div_num(t_vec v, double s);
// utils
t_data *init_data(void);
void free_data(t_data *data);
void	throw_error(t_data *data);

#endif
