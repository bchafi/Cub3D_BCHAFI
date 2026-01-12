/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:28:41 by often             #+#    #+#             */
/*   Updated: 2026/01/11 14:36:11 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./parcing.h"
# include <math.h>
# include <limits.h>
# include <float.h>
# include "./mlx_linux/mlx.h"

# ifndef HEIGHT
#  define HEIGHT 768
# endif

# ifndef WIDTH
#  define WIDTH 1024
# endif

# ifndef CUBE_DIM
#  define CUBE_DIM 64
# endif

# ifndef FATAL
#  define FATAL 44
# endif

# ifndef ESCP
#  define ESCP 65307
# endif

# ifndef W_KEY
#  define W_KEY 119
# endif

# ifndef A_KEY
#  define A_KEY 97
# endif

# ifndef S_KEY
#  define S_KEY 115
# endif

# ifndef D_KEY
#  define D_KEY 100
# endif

# ifndef ARROW_RIGHT
#  define ARROW_RIGHT 65363
# endif

# ifndef ARROW_LEFT
#  define ARROW_LEFT 65361
# endif

# ifndef BACKGROUND
#  define BACKGROUND 0x404040
# endif

# ifndef RAY_COLOR
#  define RAY_COLOR 0x0000FF
# endif

# ifndef RED
#  define RED 0xFF0000
# endif

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef ROTATION_ANGLE
#  define ROTATION_ANGLE 0.2094395102
# endif

# ifndef LEFT
#  define LEFT 1
# endif

# ifndef RIGHT
#  define RIGHT -1
# endif

# ifndef YES
#  define YES 1
# endif

# ifndef NO
#  define NO 0
# endif

# ifndef HORIZONTAL
#  define HORIZONTAL 1
# endif

# ifndef VERTICAL
#  define VERTICAL 0
# endif

# ifndef FREE_ONE
#  define FREE_ONE 1
# endif

# ifndef FREE_ALL
#  define FREE_ALL 9
# endif

typedef struct s_gcollct
{
	void				*ptr;
	struct s_gcollct	*next;
}	t_gcollct;

typedef struct s_intersection
{
	float	angle;
	float	x;
	float	y;
	float	distance;
	int		is_vertical;
}	t_intersection;

typedef struct s_calcul
{
	float	x_h;
	float	y_h;
	float	x_v;
	float	y_v;
	float	x_i;
	float	y_i;
	int		check_y;
	float	bias_y;
	int		check_x;
	float	bias_x;
}	t_calcul;

typedef struct s_ray
{
	int				id;
	t_intersection	*horizontal;
	t_intersection	*vertical;
	t_intersection	*nearest;
	struct s_ray	*next;
}	t_ray;

typedef struct s_texture
{
	void	*texture_img;
	char	*addr;
	int		bpp;
	int		height;
	int		width;
	int		endian;
	int		line_lenght;
}	t_texture;

typedef struct s_key_events
{
	float	move_speed;
	float	new_x;
	float	new_y;
	int		moved;
	float	direction;
	float	strafe_angle;
}	t_key_events;

typedef struct s_unit
{
	float			player_posx;
	float			player_posy;
	float			dir_vec_x;
	float			dir_vec_y;
	int				key_w;
	int				key_s;
	int				key_a;
	int				key_d;
	int				key_left;
	int				key_right;
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
	t_var			*map_s;
	t_ray			*ray;
	t_intersection	*horizontal;
	t_intersection	*vertical;
	t_texture		texture[4];
	float			view_angle;
	float			ang_between_rays;
	float			proj_plane_dist;
	int				maplinemax;
	int				*lenght_line_map;
	t_ray			**ray_array;
	int				map_width;
}	t_unit;

typedef struct s_geometrie
{
	float	ray_vec_x;
	float	ray_vec_y;
	float	angle;
	int		column_id;
}	t_geometrie;

typedef struct s_draw
{
	unsigned int	color;
	t_texture		*texture;
	float			partition;
	float			step;
	float			tex_pos;
	int				draw_end;
	int				draw_start;
	int				tex_x;
	int				y;
	int				offset;
	char			*pixel_addr;
	int				tex_y;
}	t_draw;

int					key_press(int keycode, t_unit *vars);
int					key_release(int keycode, t_unit *vars);
int					handle_rotation(t_unit *data, float rot_speed);
int					handle_movement(t_unit *data, float speed);
int					update_loop(t_unit *data);
int					check_ifwall(t_unit *data, int x, int y);
// int					key_events(int key);
int					close_window(void);
int					keyevent_rest(int key, t_unit *data, t_key_events *keys);

t_intersection		*smallest(t_intersection *vertical,
						t_intersection *horizontal);
void				initiating(t_unit *core);
void				flush(void);
void				write_pixel(t_unit *data, int x, int y, int color);
void				safe_pixel_write(t_unit *data, int x, int y, int color);
void				apply_rotation(t_unit *data, float sens);
void				*ft_malloc(size_t i);
void				ft_free(void *ptr, int flag);
void				search_gcollct(t_gcollct *head, void *ptr,
						t_gcollct **ret);
void				wipe_all(t_gcollct *head);
void				create_ray(t_unit *data, t_intersection *vertical,
						t_intersection *horizontal, int id);
void				draw_walls(t_unit *data);
void				alpha(t_unit *data, int column_id);
void				print_data(t_unit *data);
void				find_horizontal_intersection(t_unit *data,
						t_geometrie geom);
void				find_vertical_intersection(t_unit *data,
						t_geometrie geom);
void				ray_inbulk(t_unit *data);
void				set_ray(t_unit *data, int choice,
						float coordinates[3], int column_id);
void				ray_casting_entry(t_var *map, char **new);
void				char_direction(t_unit *data, char d);
void				draw_straps(t_unit *data, int column, float height,
						t_intersection *nearest);
void				texture_initiation(t_unit *data);
void				free_textures(t_unit *data);
void				arrows_handle(t_unit *data, int key);
void				perform_movement(t_unit *data, float new_x, float new_y);
void				lenght_of_map(char **map, t_unit *data);
void				find_vertical_rest(t_calcul calcul,
						t_geometrie geom, t_unit *data);
float				normalize_angle(float angle);

t_unit				*holder(t_unit *data);
t_ray				*find_ray_byid(t_unit *data, int id);

int					intial_horiz(t_unit *data, float ray_vec_x,
						float ray_vec_y, float *coordi[3]);
int					intial_vert(t_unit *data, float ray_vec_x,
						float ray_vec_y, float *coordi[3]);

#endif
