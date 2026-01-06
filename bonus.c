/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:24:48 by bkali             #+#    #+#             */
/*   Updated: 2026/01/06 11:09:02 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_press(int keycode, t_unit *vars)
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

int key_release(int keycode, t_unit *vars)
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

int update_loop(t_unit *data)
{
    float   move_speed = 5.0f; // Slower speed for smooth loop
    float   rot_speed = 0.07f; // Rotation speed
    int     moved = 0;
    float   new_x;
    float   new_y;

    // 1. Handle Rotation
    if (data->key_right)
    {
        data->angle -= rot_speed;
        moved = 1;
    }
    if (data->key_left)
    {
        data->angle += rot_speed;
        moved = 1;
    }

    // 2. Handle Movement (W/S)
    if (data->key_w || data->key_s)
    {
        float direction = (data->key_w) ? move_speed : -move_speed;
        new_x = data->player_posx + direction * cos(data->angle);
        new_y = data->player_posy + direction * sin(data->angle);
        perform_movement(data, new_x, new_y);
        moved = 1;
    }

    // 3. Handle Strafing (A/D)
    if (data->key_a || data->key_d)
    {
        float strafe_angle = data->angle + (M_PI / 2.0);
        float direction = (data->key_a) ? move_speed : -move_speed; // A is positive strafe here
        
        new_x = data->player_posx + direction * cos(strafe_angle);
        new_y = data->player_posy + direction * sin(strafe_angle);
        perform_movement(data, new_x, new_y);
        moved = 1;
    }

    // 4. Redraw ONLY if something changed
    if (moved)
    {
        // Update ray tip for visual debugging if you use it
        data->ray_tip_x = data->player_posx + 80 * cos(data->angle);
        data->ray_tip_y = data->player_posy + 80 * sin(data->angle);

        alpha(data, 0); // Raycasting
        mlx_put_image_to_window(data->mlx, data->mlx_window, data->img, 0, 0);
    }
    return (0);
}