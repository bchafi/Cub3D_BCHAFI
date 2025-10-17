/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 09:00:14 by yrhandou          #+#    #+#             */
/*   Updated: 2025/08/26 14:23:58 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/**
 * To close the window using the mouse
 */
void ft_close(void *param)
{
	t_cube *cub;

	cub = (t_cube *)param;
	mlx_delete_image(cub->mlx, cub->img);
	mlx_close_window(cub->mlx);
	printf("CLOSED");
	return;
}
/**
 * To close the window using the ESC button
 */
void esc_close(mlx_key_data_t keydata, void *param)
{
	t_cube *cub;
	(void)keydata;
	
	cub = (t_cube *)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(cub->mlx, cub->img);
		mlx_close_window(cub->mlx);
		printf("CLOSED BY ESC");
	}
}


