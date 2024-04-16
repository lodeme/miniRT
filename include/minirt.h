
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

// vector operations

// utils
t_data *init_data(void);
void free_data(t_data *data);
void	throw_error(t_data *data);

#endif
