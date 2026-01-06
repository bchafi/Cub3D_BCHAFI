/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 18:28:03 by sel-mir           #+#    #+#             */
/*   Updated: 2026/01/06 08:29:12 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_intersection	*smallest(t_intersection *vertical, t_intersection *horizontal)
{
	if ((*vertical).distance > (*horizontal).distance)
		return (horizontal);
	else
		return (vertical);
}

void	updatepage(t_unit *data, t_key_events *keys)
{
	if ((*keys).moved)
	{
		(*data).ray_tip_x = (*data).player_posx + 80 * cos((*data).angle);
		(*data).ray_tip_y = (*data).player_posy + 80 * sin((*data).angle);
		alpha(data, 0);
		mlx_put_image_to_window((*data).mlx,
			(*data).mlx_window, (*data).img, 0, 0);
	}
}

int	keyevent_rest(int key, t_unit *data, t_key_events *keys)
{
	if (key == W_KEY || key == S_KEY)
	{
		if (key == W_KEY)
			(*keys).direction = (*keys).move_speed;
		else
			(*keys).direction = -(*keys).move_speed;
		(*keys).new_x = data->player_posx
			+ (*keys).direction * cos(data->angle);
		(*keys).new_y = data->player_posy
			+ (*keys).direction * sin(data->angle);
		perform_movement(data, (*keys).new_x, (*keys).new_y);
		(*keys).moved = 1;
	}
	if (key == ARROW_LEFT || key == ARROW_RIGHT)
	{
		arrows_handle(data, key);
		(*keys).moved = 1;
	}
	updatepage(data, keys);
	return (0);
}

t_unit	*holder(t_unit *data)
{
	static t_unit	*precious;

	if (!precious)
		precious = data;
	return (precious);
}
