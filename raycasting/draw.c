/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:09:02 by yrhandou          #+#    #+#             */
/*   Updated: 2025/09/07 11:54:12 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void draw_rectangle(mlx_image_t *img, t_obj *obj)
{
	int i;
	int j;

	i = obj->pos.Y;
	j = obj->pos.X;
	while (i < obj->height + obj->pos.Y)
	{
		j = obj->pos.X;
		while (j < obj->width + obj->pos.X)
		{
			mlx_put_pixel(img, j, i, obj->color);
			j++;
		}
		i++;
	}
}

void draw_bresenhamline(t_cube *cub, t_vector dest, uint32_t color)
{
	t_vector plyrMapPos;
	mlx_instance_t *plyrInstPos;
	t_vector *rayOrigin = NULL; // new

	plyrMapPos= cub->plyr->mapPosition;
	plyrInstPos= cub->plyr->instancePosition;
	plyrInstPos->x += 5;
	plyrInstPos->y += 5 ;
	// ? (initial subray) should start here
	t_vector *delta = sub_vec(&dest, rayOrigin);
	int decision = 2 * delta->Y - delta->X;
	int initY = rayOrigin->Y;
	while(rayOrigin->X <= dest.X)
	{
		mlx_put_pixel(cub->PlyrImg, rayOrigin->X,  initY, color);
		if(decision > 0)
		{
			initY++;
			decision = decision - 2*delta->X;
		}
		decision = decision + 2*delta->Y;
		rayOrigin->X++;
	}
	clean_vec(delta);
}

void draw_plyr(t_cube *cub)
{
	mlx_instance_t *instancePosition;
	t_vector mapPosition;
	t_obj obj;

	instancePosition = cub->plyr->instancePosition;
	update_vec(&mapPosition, instancePosition->x,instancePosition->y );
	mapPosition = scaleToMap(mapPosition);
	obj = set_obj( 15, 15, (mlx_instance_t *)&mapPosition, BLUE);
	draw_rectangle(cub->PlyrImg, &obj);
	print_vec((t_vector *)instancePosition);
}

void draw_map(void *param)
{
	t_vector pos2d;
	t_cube *cub;
	char **map;
	t_obj obj;
	uint32_t color;

	pos2d.Y = 0;
	cub = ((t_cube *)(param));
	map = cub->map;
	while (map[pos2d.Y])
	{
		pos2d.X = 0;
		while (map[pos2d.Y][pos2d.X])
		{
			if (map[pos2d.Y][pos2d.X] == '1')
				color = GREY;
			else
				color = GREEN;
			obj = set_obj(TILE_SIZE, TILE_SIZE, &(mlx_instance_t){pos2d.X * 32, pos2d.Y * 32, 1, true}, color);
			draw_rectangle(cub->MapImg, &obj);
			pos2d.X++;
		}
		pos2d.Y++;
	}
}

/**
 * @brief Creates a timer that runs for every frame
 * @param param cube_t *
 */
void draw_timer(void *param)
{
	t_cube *cub;

	cub = (t_cube *)param;
	char buffer[1000];
	sprintf(buffer, "Timer : %f", mlx_get_time());
	if (cub->timer)
		mlx_delete_image(cub->mlx, cub->timer);
	if (cub->hide_timer == 0)
		cub->timer = mlx_put_string(cub->mlx, buffer, 800, 600);
}
