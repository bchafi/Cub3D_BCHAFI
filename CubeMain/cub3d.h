# ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./mlx_linux/mlx.h"
#include <limits.h>
#include <float.h>
#include "./parcing.h"


#ifndef FATAL
# define FATAL 44
#endif

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#ifndef HEIGHT
#define HEIGHT 768
#endif

#ifndef WIDTH 
#define WIDTH 1024
#endif

#ifndef LEFT
#define LEFT 1
#endif

#ifndef RIGHT
#define RIGHT -1
#endif

#ifndef ESCP 
#define ESCP 65307
#endif

#ifndef W_key 
#define W_key 119
#endif

#ifndef A_key 
#define A_key 97
#endif

#ifndef S_key 
#define S_key 115
#endif

#ifndef D_key 
#define D_key 100
#endif

#ifndef Arrow_right
#define Arrow_right 65363
#endif

#ifndef Arrow_left 
#define Arrow_left 65361
#endif

#ifndef BACKGROUND 
#define BACKGROUND 0x404040
#endif

#ifndef RAY_COLOR 
#define RAY_COLOR 0x0000FF
#endif

#ifndef CUBE_DIM
#define CUBE_DIM 64
#endif

#ifndef VIEW_ANGLE
#define VIEW_ANGLE (M_PI/3)
#endif

#ifndef ANG_BETWEEN_RAYS
#define ANG_BETWEEN_RAYS (VIEW_ANGLE/WIDTH)
#endif

#ifndef YES
#define YES 1
#endif

#ifndef NO
#define NO 0
#endif

#ifndef RED
#define RED 0xFF0000
#endif

#ifndef PROJ_PLANE_DIST
#define PROJ_PLANE_DIST 277.0f 
#endif

#ifndef Rotation_Angle 
#define Rotation_Angle (M_PI / 15.0) 
#endif

#ifndef	HORIZONTAL
#define HORIZONTAL 1
#endif

#ifndef	VERTICAL
#define VERTICAL 0
#endif

# define FREE_ONE 1

# define FREE_ALL 9

typedef struct s_gcollct
{
	void				*ptr;
	struct s_gcollct	*next;
}	t_gcollct;

typedef	struct s_intersection
{
	float	angle;
	float		x;
	float		y;
	float		distance;
	int			is_vertical;
}	t_intersection;

typedef	struct	s_ray
{
	int				id;
	t_intersection	*horizontal;
	t_intersection	*vertical;
	t_intersection	*nearest;
	struct s_ray	*next;
}	t_ray;

typedef struct s_texture
{
	void			*texture_img;
	char 			*addr;
	int 			bpp;
	int 			height;
	int 			width;
	int				endian;
	int				line_lenght;

} t_texture ;

typedef struct s_unit
{
	float				player_posx;
	float				player_posy;
	uint32_t		celling_color;
	uint32_t		floor_color;
	
	float			dir_vec_x;
	float			dir_vec_y;

	float			ray_tip_x;
	float			ray_tip_y;
	float			angle;
	void			*mlx;
	void			*mlx_window;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	double			zoom;
	char			**map;
	t_ray			*ray;
	t_intersection	*horizontal;
	t_intersection	*vertical;
	t_texture		texture[4];
	t_var			*vars;
	int fd;
}	t_unit;

void	initiating(t_unit *core);
void	flush(t_unit *data);
void	write_pixel(t_unit *data, int x, int y, int color);
void	safe_pixel_write(t_unit *data, int x, int y, int color);
void	draw_player(t_unit *data, int pos_x, int pos_y);
void	player_pos_clean(t_unit *data, int pos_x, int pos_y, int backgrnd_color);
void	apply_rotation(t_unit *data, float sens);
void	*ft_malloc(size_t size);
void	ft_free(void *ptr, int flag);
void	search_gcollct(t_gcollct *head, void *ptr, t_gcollct **ret);
void	wipe_all(t_gcollct *head);
void	create_ray(t_unit *data, t_intersection *vertical, t_intersection *horizontal, int id);
void	Draw_Walls(t_unit *data);
void	alpha(t_unit *data, int column_id);
void	draw_column(t_unit *data, int height, int column, t_intersection *nearest);
void	print_data(t_unit *data);
void	find_horizontal_intersection(t_unit *data, float ray_vec_x, float ray_vec_y, float angle, int column_id);
void	find_vertical_intersection(t_unit *data, float ray_vec_x, float ray_vec_y, float angle, int column_id); // Changed int to float
void	ray_inbulk(t_unit *data);
void	set_ray(t_unit *data, int choice, float coordinates[3], int column_id);
void	ray_casting_entry(t_var* map);
void	char_direction(t_unit *data,  char d);
void	draw_straps(t_unit *data, int column, float height, t_intersection *nearest);
void	texture_initiation(t_unit *data, t_var *map);
void	free_textures(t_unit *dataa);

float normalize_angle(float angle);

t_intersection	*smallest(t_intersection *vertical, t_intersection *horizontal);

t_unit	*holder(t_unit *data);

t_ray	*find_ray_byid(t_unit *data, int id);

int	check_ifwall(t_unit *data, int x, int y);
int		key_events(int key, t_unit *data);
int	close_window(t_unit *da);


int	intial_horiz(t_unit *data, float ray_vec_x, float ray_vec_y, float *coordi[3]); // Changed int to float
int	intial_vert(t_unit *data, float ray_vec_x, float ray_vec_y, float *coordi[3]); // Changed int to float

#endif
