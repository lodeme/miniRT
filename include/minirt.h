
#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 1280
# define HEIGHT 720

# define SUCCESS 0
# define FAILURE 1

#include "libft.h"
#include "MLX42/MLX42.h"
#include <math.h>

typedef struct s_data
{
  mlx_t       *win;
  mlx_image_t *img;
} t_data;

typedef struct s_vec
{
  double x;
  double y;
  double z;
} t_vec;

typedef struct s_col
{
  int r;
  int g;
  int b;
  int a;
} t_col;

// colors
int calc_color(int r, int g, int b, int a);

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

// utils
t_data *init_data(void);
void free_data(t_data *data);
void	throw_error(t_data *data);

#endif
