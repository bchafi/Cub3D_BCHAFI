/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:50:47 by yrhandou          #+#    #+#             */
/*   Updated: 2025/09/06 16:55:32 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * To close the window using the ESC button
 */
void handle_esc(t_cube *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_cleanup(cub);
		printf("CLOSED BY ESC");
	}
}

void handle_timer(t_cube *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_H))
	{
		mlx_delete_image(cub->mlx, cub->timer);
		cub->hide_timer = !cub->hide_timer;
		printf("toggle Timer \n");
	}
}

void handle_mouvement(t_cube *cub,mlx_key_data_t keydata)
{
	t_player *plyr;

	plyr = cub->plyr;
	if ((keydata.key >= MLX_KEY_RIGHT && keydata.key <= MLX_KEY_UP )
	&& mlx_is_key_down(cub->mlx, keydata.key))
		update_plyrWinPos(cub, 5, 5, keydata.key);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_P))
	{
		printf("Player Position X :%d Y:%d \n", cub->plyr->mapPosition.X , cub->plyr->mapPosition.Y);
	}
}

/**
 * To close the window using the mouse
 */
void ft_close(void *param)
{
	t_cube *cub;

	cub = (t_cube *)param;
	// mlx_cleanup(cub);
	printf("CLOSED WINDOW ");
}

void handle_mouse_events(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_cube *cub;
	int	x;
	int	y;
	(void)mods;
	cub = (t_cube *)param;
	 if(button == MLX_MOUSE_BUTTON_LEFT &&( action == MLX_PRESS || action == MLX_RELEASE ))
	 {
	 	mlx_get_mouse_pos(cub->mlx, &x , &y);
		printf("Xpos: %d, Ypos:%d\n", x,y);
	 }
}

void handle_input(mlx_key_data_t keydata, void *param)
{
	t_cube *cub;

	cub = (t_cube *)param;
	handle_esc(cub);
	handle_mouvement(cub, keydata);
	handle_timer(cub);
}
