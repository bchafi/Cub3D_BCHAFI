/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 10:59:10 by yrhandou          #+#    #+#             */
/*   Updated: 2025/09/06 16:35:51 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int ft_is_player(char c)
{
	return (c == 'N' || c =='S' || c == 'E' || c =='W');
}

t_obj set_obj(int width, int height, mlx_instance_t *pos, uint32_t color)
{
	t_obj obj;

	obj.width = width;
	obj.height = height;
	obj.pos.X = pos->x;
	obj.pos.Y = pos->y;
	obj.color = color;
	return obj;
}

t_vector scaleToInstance(t_vector mapPosition)
{
	t_vector InstancePosition;

	InstancePosition.X = mapPosition.X * TILE_SIZE;
	InstancePosition.Y = mapPosition.Y * TILE_SIZE;
	return InstancePosition;
}
t_vector scaleToMap(t_vector InstancePosition)
{
	t_vector mapPosition;

	mapPosition.X = InstancePosition.X / TILE_SIZE;
	mapPosition.Y = InstancePosition.Y / TILE_SIZE;
	return mapPosition;
}

bool mapCheck(t_cube *cub, t_vector *mapPosition)
{
	if(cub->map[mapPosition->Y][mapPosition->X] == '1')
		return 0;
	return 1;
}
