#ifndef CUB3D_H
# define CUB3D_H

# include "./parcing.h"
# include <math.h>
# include <limits.h>
# include <float.h>
# include "./mlx_linux/mlx.h"

#  define HEIGHT 768
#  define WIDTH 1024
#  define CUBE_DIM 64
#  define ESCP 65307
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define ARROW_RIGHT 65363
#  define ARROW_LEFT 65361

typedef struct s_unit
{
	// --- RAYCASTING (The Camera) ---
    double      pos_x;
    double      pos_y;      
    double      dir_x;
    double      dir_y;      
    double      plane_x;
    double      plane_y;
}	t_unit;

void    raycast_engine(t_var *vars);


#endif
