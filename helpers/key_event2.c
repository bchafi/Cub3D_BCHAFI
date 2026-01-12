/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:24:48 by bkali             #+#    #+#             */
/*   Updated: 2026/01/11 18:05:15 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_rotation(t_unit *data, float rot_speed)
{
	if (data->key_right)
	{
		data->angle -= rot_speed;
		return (1);
	}
	if (data->key_left)
	{
		data->angle += rot_speed;
		return (1);
	}
	return (0);
}

int	move_logic(t_unit *data, float speed, double angle_offset, int key_p)
{
	float	dir;
	float	nx;
	float	ny;

	if (key_p)
		dir = speed;
	else
		dir = -speed;
	nx = data->player_posx + dir * cos(data->angle + angle_offset);
	ny = data->player_posy + dir * sin(data->angle + angle_offset);
	perform_movement(data, nx, ny);
	return (1);
}

int	handle_movement(t_unit *data, float speed)
{
	int	moved;

	moved = 0;
	if (data->key_w || data->key_s)
		moved += move_logic(data, speed, 0, data->key_w);
	if (data->key_a || data->key_d)
		moved += move_logic(data, speed, M_PI / 2.0, data->key_a);
	return (moved);
}

int	update_loop(t_unit *data)
{
	int	moved;

	moved = 0;
	moved += handle_rotation(data, 0.05f);
	moved += handle_movement(data, 5.0f);
	if (moved)
	{
		data->ray_tip_x = data->player_posx + 80 * cos(data->angle);
		data->ray_tip_y = data->player_posy + 80 * sin(data->angle);
		alpha(data, 0);
		mlx_put_image_to_window(data->mlx, data->mlx_window,
			data->img, 0, 0);
	}
	return (0);
}
