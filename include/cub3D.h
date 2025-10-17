/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:05:06 by yrhandou          #+#    #+#             */
/*   Updated: 2025/08/26 16:03:27 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H
#define _CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "MLX42.h"

#define WIDTH 1007
#define HEIGHT 641

enum e_color
{
	RED = 0xFF0000FF,
	GREEN = 0x00FF00FF,
	BLUE = 0x0000FFFF,
};

typedef struct s_plyr
{
	int Xpos;
	int Ypos;
} t_plyr;

typedef struct s_obj
{
	size_t width;
	size_t height;
	size_t Xpos;
	size_t Ypos;
} t_obj;

typedef struct s_cube
{
	mlx_t *mlx;
	mlx_image_t *timer;
	mlx_image_t *img;
	t_plyr *player;
	char **map;
} t_cube;

int cub_init(t_cube *cub);
void ft_close(void *param);
void esc_close(mlx_key_data_t keydata, void *param);
int ft_is_player(char c);


#endif
