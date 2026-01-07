/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* Draw.c                                             :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/01/03 18:25:29 by sel-mir           #+#    #+#             */
/* Updated: 2026/01/07 19:55:00 by sel-mir          ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_walls(t_unit *data)
{
	static int	flag;
	t_ray		*ray;
	float		height;

	ray = (*data).ray;
	flag++;
	while (ray)
	{
		height = (CUBE_DIM / (*(*ray).nearest).distance)
		* data->proj_plane_dist;
		
		draw_straps(data, (*ray).id, (int)height, (*ray).nearest);
		ray = (*ray).next;
	}
	mlx_put_image_to_window((*data).mlx, (*data).mlx_window, (*data).img, 0, 0);
}

void	fix_mirroring(float *partition, t_texture **Var,
		t_unit *data, t_intersection *intersection)
{
	if (!intersection->is_vertical)
	{
		if (sin(intersection->angle) < 0)
			*Var = &(data->texture[0]);
		else
		{
			*Var = &(data->texture[1]);
			*partition = 1.0 - *partition;
		}
	}
	else
	{
		if (cos(intersection->angle) > 0)
			*Var = &(data->texture[3]);
		else
		{
			*Var = &(data->texture[2]);
			*partition = 1.0 - *partition;
		}
	}
}

// This function Get u which strap of the texture image to draw
//	based on which part of the wall the ray hit !

void	initialyze_strapping(t_unit *data,
		t_intersection *nearest, t_draw *drawing)
{
	(*drawing).partition = nearest->x;
	if (nearest->is_vertical)
		(*drawing).partition = nearest->y;
	(*drawing).partition = (*drawing).partition / CUBE_DIM;
	(*drawing).partition -= floor((*drawing).partition);
	if ((*drawing).partition >= 1.0)
		(*drawing).partition = 0.9999;
	if ((*drawing).partition < 0)
		(*drawing).partition = 0;
	fix_mirroring(&((*drawing).partition),
		&((*drawing).texture), data, nearest);
	(*drawing).tex_x = (int)((*(*drawing).texture).width
			* (*drawing).partition);
}

void	draw_textures(t_unit *data, t_draw *drawing, int column)
{
	while ((*drawing).y < (*drawing).draw_end)
	{
		(*drawing).tex_y = (int)(*drawing).tex_pos;
		if ((*drawing).tex_y >= (*((*drawing).texture)).height)
			(*drawing).tex_y = (*((*drawing).texture)).height - 1;
		if ((*drawing).tex_y < 0)
			(*drawing).tex_y = 0;
		(*drawing).tex_pos += (*drawing).step;
		if ((*drawing).tex_x >= (*((*drawing).texture)).width)
			(*drawing).tex_x = (*((*drawing).texture)).width - 1;
		if ((*drawing).tex_x < 0)
			(*drawing).tex_x = 0;
		(*drawing).offset = ((*drawing).tex_y
				* (*((*drawing).texture)).line_lenght)
			+ ((*drawing).tex_x * ((
						*((*drawing).texture)).bpp / 8));
		(*drawing).pixel_addr = (
				*((*drawing).texture)).addr + (*drawing).offset;
		(*drawing).color = *(unsigned int *)(*drawing).pixel_addr;
		safe_pixel_write(data, column, (*drawing).y, (*drawing).color);
		(*drawing).y++;
	}
}

void	draw_straps(t_unit *data, int column,
	float height, t_intersection *nearest)
{
	t_draw	drawing;

	if (height <= 0)
		return ;
	initialyze_strapping(data, nearest, &drawing);
	drawing.draw_start = (HEIGHT - height) / 2;
	drawing.draw_end = (HEIGHT + height) / 2;
	if (drawing.draw_start < 0)
		drawing.draw_start = 0;
	if (drawing.draw_end >= HEIGHT)
		drawing.draw_end = HEIGHT;
	drawing.y = 0;
	while (drawing.y < drawing.draw_start)
		safe_pixel_write(data, column, drawing.y++, data->map_s->earth_color);
	drawing.step = 1.0 * (*(drawing.texture)).height / height;
	drawing.tex_pos = (drawing.draw_start
			- (HEIGHT - height) / 2) * drawing.step;
	drawing.y = drawing.draw_start;
	draw_textures(data, &drawing, column);
	while (drawing.y < HEIGHT)
		safe_pixel_write(data, column, drawing.y++, data->map_s->floor_color);
}
