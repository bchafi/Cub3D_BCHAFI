/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:05:06 by yrhandou          #+#    #+#             */
/*   Updated: 2025/09/07 14:02:30 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H
#define _CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "MLX42.h"
#include "../libft/libft.h"

#define WIDTH 1007
#define HEIGHT 641
#define TILE_SIZE 30


// <<<<<<<<<<<< Start Parsng >>>>>>>>>>>>
#include <fcntl.h>

// typedef struct info
// {
	
// }	t_info;
char **parsing_map(int fd);


// <<<<<<<<<<<<< End Parsng >>>>>>>>>>>>>>


enum e_color
{
	EMPTY= 0x00000000,
	GREY = 0x808080FF,
	BLUE = 0x0000FFFF,
	GREEN = 0x00FF00FF,
	RED = 0xFF0000FF,
	YELLOW = 0xFFFF00FF,
	WHITE = 0xFFFFFFFF,
};

typedef struct s_vector
{
	int		X;
	int		Y;
} t_vector;

typedef struct s_vectoir
{
	float		X;
	float		Y;
} t_vectoir;
typedef struct s_plyr
{
	t_vector mapPosition;
	mlx_instance_t *instancePosition;
	char	direction;
	int32_t inst;
} t_player;

typedef struct s_obj
{
	int width;
	int height;
	t_vector pos;
	uint32_t color;
} t_obj;

typedef struct s_cube
{
	mlx_t *mlx;
	mlx_image_t *timer;
	int hide_timer ;
	mlx_image_t *MapImg;
	mlx_image_t *PlyrImg;
	t_player *plyr;
	char **map;
} t_cube;


/*------------------*/
int cub_init(t_cube *cub, char *arg);
void ft_close(void *param);
void mlx_cleanup(t_cube *cub);
void handle_mouse_events(mouse_key_t button, action_t action, modifier_key_t mods, void* param);
void handle_input(mlx_key_data_t keydata, void *param);
/*------------------*/

void draw_map(void *param);
void draw_timer(void * param);
void draw_texture(t_cube *cub);
void draw_ray(t_cube *cub, int i , int j, uint32_t color);
void draw_rectangle(mlx_image_t *img, t_obj *obj);
void draw_bresenhamline(t_cube *cub, t_vector dest, uint32_t color);

/*------------------*/

t_obj set_obj(int width, int height, mlx_instance_t *pos, uint32_t color);
int ft_is_player(char c);
t_player *set_playerPosition(char **map);
bool mapCheck(t_cube *cub, t_vector *mapPosition);
void draw_plyr(t_cube *cub);
mlx_instance_t *update_plyrWinPos(t_cube *cub, int i, int j, keys_t key);
t_vector scaleToInstance(t_vector mapPosition);
t_vector scaleToMap(t_vector InstancePosition);
/*------------------*/
// ! free_player is dangerous
void free_arr(void **arr);
void free_player(t_player *plyr);

/*------------------*/

t_vector *create_vector(int i, int j);
t_vector *print_vec(t_vector *vec);
t_vector *add_vec(t_vector *vec_A, t_vector *vec_B );
t_vector *advance_vec(t_vector *vec, int val);
t_vector *sub_vec(t_vector *vec_A, t_vector *vec_B );
t_vector *update_vec(t_vector *vec, int x, int y);
void clean_vec(t_vector *vec);

#endif
