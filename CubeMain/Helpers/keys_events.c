/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 20:24:37 by sel-mir           #+#    #+#             */
/*   Updated: 2026/01/05 06:02:31 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    arrows_handle(t_unit *data, int key)
{
    if (key == Arrow_right)
    {
        apply_rotation(data, -1.0);
    }
    if (key == Arrow_left)
    {
        apply_rotation(data, 1.0);
    }
}


static void    perform_movement(t_unit *data, float new_x, float new_y)
{
    if (check_ifwall(data, new_x, (*data).player_posy) == NO)
    {
        (*data).player_posx = new_x;
    }
    if (check_ifwall(data, (*data).player_posx, new_y) == NO)
    {
        (*data).player_posy = new_y;
    }
}

int key_events(int key, t_unit *data)
{
    float   move_speed = 20.0f;
    float   new_x;
    float   new_y;
    int     moved = 0;

    if (key == ESCP)
		close_window(data);
    if (key == W_key || key == S_key)
    {
        float direction = (key == W_key) ? move_speed : -move_speed;
        
        new_x = (*data).player_posx + direction * cos((*data).angle);
        new_y = (*data).player_posy + direction * sin((*data).angle);
        perform_movement(data, new_x, new_y);
        moved = 1;
    }

    if (key == A_key || key == D_key)
    {
        float strafe_angle = (*data).angle + (M_PI / 2.0); 
        float direction = (key == A_key) ? move_speed : -move_speed;
        
        new_x = (*data).player_posx + direction * cos(strafe_angle);
        new_y = (*data).player_posy + direction * sin(strafe_angle);
        perform_movement(data, new_x, new_y);
        moved = 1;
    }
    
    if (key == Arrow_left || key == Arrow_right)
    {
        arrows_handle(data, key);
        moved = 1;
    }
    if (moved)
    {
        (*data).ray_tip_x = (*data).player_posx + 80 * cos((*data).angle);
        (*data).ray_tip_y = (*data).player_posy + 80 * sin((*data).angle);

        alpha(data, 0);
        mlx_put_image_to_window((*data).mlx, (*data).mlx_window, (*data).img, 0, 0);
    }
    return (0);
}

void	flush(t_unit *data)
{
    ft_free_alls((*data).vars);
	ft_free(NULL, FREE_ALL);
}

void	initiating(t_unit *core)
{
	(*core).mlx = mlx_init();
	if (!(*core).mlx)
		flush(core);
	(*core).mlx_window = mlx_new_window((*core).mlx, WIDTH, HEIGHT, "Alpha");
	if (!(*core).mlx_window)
		flush(core);
	(*core).img = mlx_new_image((*core).mlx, WIDTH, HEIGHT);
	if (!(*core).img)
	{
		mlx_destroy_window((*core).mlx, (*core).mlx_window);
		flush(core);
	}
	(*core).addr = mlx_get_data_addr((*core).img,
			&(*core).bits_per_pixel, &(*core).line_length, &(*core).endian);
	if (!(*core).addr)
	{
		mlx_destroy_window((*core).mlx, (*core).mlx_window);
		mlx_destroy_image((*core).mlx, (*core).img);
		flush(core);
	}
}
