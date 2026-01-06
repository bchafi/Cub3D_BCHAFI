/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray_Casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:57:55 by sel-mir           #+#    #+#             */
/*   Updated: 2026/01/05 15:30:00 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	alpha(t_unit *data, int column_id)
{
	t_geometrie	geom;
	float		strt_angle;
	float		ray_vec_x;
	float		ray_vec_y;

	strt_angle = (*data).angle + ((*data).view_angle / 2.0);
	while (strt_angle >= (*data).angle
		- ((*data).view_angle / 2.0) && column_id < WIDTH)
	{
		ray_vec_x = cos(strt_angle);
		ray_vec_y = sin(strt_angle);
		geom.ray_vec_x = ray_vec_x;
		geom.ray_vec_y = ray_vec_y;
		geom.angle = strt_angle;
		geom.column_id = column_id;
		find_horizontal_intersection(data, geom);
		find_vertical_intersection(data, geom);
		strt_angle -= (*data).ang_between_rays;
		column_id++;
	}
	draw_walls(data);
}

void	find_horizontal_rest(t_calcul calcul, t_geometrie geom, t_unit *data)
{
	while (1)
	{
		if (calcul.x_h < 0 || calcul.y_h < 0)
			return (set_ray(data, HORIZONTAL,
					(float []){-1, -1, -1}, geom.column_id), (void) 0);
		calcul.check_y = (int)calcul.y_h;
		if (geom.ray_vec_y < 0)
			calcul.check_y = (int)calcul.y_h - 1;
		if (geom.ray_vec_x > 0)
			calcul.bias_x = 0.0001;
		else
			calcul.bias_x = -0.0001;
		if (check_ifwall(data, (int)(calcul.x_h + calcul.bias_x),
			calcul.check_y) == YES)
			return (set_ray(data, HORIZONTAL, (float []){calcul.x_h,
					calcul.y_h, geom.angle}, geom.column_id), (void)0);
		calcul.x_h += calcul.x_i;
		calcul.y_h += calcul.y_i;
	}
}

void	find_horizontal_intersection(t_unit *data, t_geometrie geom)
{
	t_calcul	calcul;

	if (geom.ray_vec_y == 0)
		return (set_ray(data, HORIZONTAL,
				(float []){-1, -1, -1}, geom.column_id), (void)0);
	intial_horiz(data, geom.ray_vec_x, geom.ray_vec_y,
		(float *[]){&(calcul.x_h), &(calcul.y_h), &geom.angle});
	if (geom.ray_vec_y < 0)
		calcul.y_i = -CUBE_DIM;
	else
		calcul.y_i = CUBE_DIM;
	calcul.x_i = calcul.y_i * (geom.ray_vec_x / geom.ray_vec_y);
	find_horizontal_rest(calcul, geom, data);
}

int	intial_horiz(t_unit *data, float ray_vec_x,
	float ray_vec_y, float *coordi[3])
{
	float	x_h;
	float	y_h;
	float	dx;
	float	dy;

	if (ray_vec_y < 0)
		y_h = ((int)(data->player_posy / CUBE_DIM) * CUBE_DIM);
	else
		y_h = ((int)(data->player_posy / CUBE_DIM) * CUBE_DIM) + CUBE_DIM;
	dy = y_h - (*data).player_posy;
	dx = dy * (ray_vec_x / ray_vec_y);
	x_h = (*data).player_posx + dx;
	*coordi[0] = x_h;
	*coordi[1] = y_h;
	return (YES);
}

void	find_vertical_rest(t_calcul calcul, t_geometrie geom, t_unit *data)
{
	while (1)
	{
		if (calcul.x_v < 0 || calcul.y_v < 0)
			return (set_ray(data, VERTICAL,
					(float []){-1, -1, -1}, geom.column_id), (void)0);
		calcul.check_x = (int)calcul.x_v;
		if (geom.ray_vec_x < 0)
			calcul.check_x = (int)calcul.x_v - 1;
		if (geom.ray_vec_y > 0)
			calcul.bias_y = 0.0001;
		else
			calcul.bias_y = -0.0001;
		if (check_ifwall(data, calcul.check_x,
				(int)(calcul.y_v + calcul.bias_y)) == YES)
			return (set_ray(data, VERTICAL,
					(float []){calcul.x_v, calcul.y_v, geom.angle},
				geom.column_id), (void)0);
		calcul.x_v += calcul.x_i;
		calcul.y_v += calcul.y_i;
	}
}
