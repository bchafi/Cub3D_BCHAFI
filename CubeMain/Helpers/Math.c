/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:24:09 by sel-mir           #+#    #+#             */
/*   Updated: 2025/11/18 16:45:19 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// In here we Apllying the rotation only for the ray_tip !

void	apply_rotation(t_unit *data, float sens)
{
	(*data).angle += Rotation_Angle * sens;
	if ((*data).angle >= 2 * M_PI)
    	(*data).angle -= 2 * M_PI;
	else if ((*data).angle < 0)
    	(*data).angle += 2 * M_PI;
	(*data).ray_tip_x = (*data).player_posx + 80 * cos((*data).angle);
	(*data).ray_tip_y = (*data).player_posy + 80 * sin((*data).angle);
}

void	char_direction(t_unit *data,  char d)
{
	if (d == 'N')
		return ((*data).angle = -(M_PI/2), (void)0);
	if (d == 'S')
		return ((*data).angle = (M_PI / 2), (void)0);
	if (d == 'W')
		return ((*data).angle = (float)M_PI, (void)0);
	if (d == 'E')
		return ((*data).angle = (float)0, (void)0);
}

float normalize_angle(float angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += 2 * M_PI;
    return angle;
}