/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:24:37 by sel-mir           #+#    #+#             */
/*   Updated: 2026/01/08 11:38:29 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	arrows_handle(t_unit *data, int key)
{
	if (key == ARROW_RIGHT)
		apply_rotation(data, -1.0);
	if (key == ARROW_LEFT)
		apply_rotation(data, 1.0);
}

void	perform_movement(t_unit *data, float new_x, float new_y)
{
	float	pad;

	pad = 10.0;
	if (check_ifwall(data, new_x + pad, data->player_posy) == NO
		&& check_ifwall(data, new_x - pad, data->player_posy) == NO)
		data->player_posx = new_x;
	if (check_ifwall(data, data->player_posx, new_y + pad) == NO
		&& check_ifwall(data, data->player_posx, new_y - pad) == NO)
		data->player_posy = new_y;
}

int	key_press(int keycode, t_unit *vars)
{
	if (keycode == ESCP)
		close_window();
	if (keycode == W_KEY)
		vars->key_w = 1;
	if (keycode == S_KEY)
		vars->key_s = 1;
	if (keycode == A_KEY)
		vars->key_a = 1;
	if (keycode == D_KEY)
		vars->key_d = 1;
	if (keycode == ARROW_LEFT)
		vars->key_left = 1;
	if (keycode == ARROW_RIGHT)
		vars->key_right = 1;
	return (0);
}

int	key_release(int keycode, t_unit *vars)
{
	if (keycode == W_KEY)
		vars->key_w = 0;
	if (keycode == S_KEY)
		vars->key_s = 0;
	if (keycode == A_KEY)
		vars->key_a = 0;
	if (keycode == D_KEY)
		vars->key_d = 0;
	if (keycode == ARROW_LEFT)
		vars->key_left = 0;
	if (keycode == ARROW_RIGHT)
		vars->key_right = 0;
	return (0);
}

// int	key_events(int key)
// {
// 	t_key_events	keys;
// 	t_unit			*data;
// 	ft_bzero(&keys, sizeof(t_key_events));
// 	data = holder(NULL);
// 	keys.move_speed = 20.0f;
// 	keys.moved = 0;
// 	if (key == ESCP)
// 		close_window();
// 	if (key == A_KEY || key == D_KEY)
// 	{
// 		keys.strafe_angle = data->angle + (M_PI / 2.0);
// 		if (key == A_KEY)
// 			keys.direction = keys.move_speed;
// 		else
// 			keys.direction = -keys.move_speed;
// 		keys.new_x = data->player_posx
// 			+ keys.direction * cos(keys.strafe_angle);
// 		keys.new_y = data->player_posy + keys.direction
// 			* sin(keys.strafe_angle);
// 		perform_movement(data, keys.new_x, keys.new_y);
// 		keys.moved = 1;
// 	}
// 	keyevent_rest(key, data, &keys);
// 	return (0);
// }

void	initiating(t_unit *core)
{
	(*core).mlx = mlx_init();
	if (!(*core).mlx)
		flush();
	(*core).mlx_window = mlx_new_window((*core).mlx, WIDTH, HEIGHT, "Alpha");
	if (!(*core).mlx_window)
		flush();
	(*core).img = mlx_new_image((*core).mlx, WIDTH, HEIGHT);
	if (!(*core).img)
	{
		mlx_destroy_window((*core).mlx, (*core).mlx_window);
		flush();
	}
	(*core).addr = mlx_get_data_addr((*core).img,
			&(*core).bits_per_pixel, &(*core).line_length, &(*core).endian);
	if (!(*core).addr)
	{
		mlx_destroy_window((*core).mlx, (*core).mlx_window);
		mlx_destroy_image((*core).mlx, (*core).img);
		flush();
	}
}
