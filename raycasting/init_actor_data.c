/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_actor_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:49:20 by yrhandou          #+#    #+#             */
/*   Updated: 2025/08/26 16:20:11 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int cub_init(t_cube *cub)
{
	int i;

	i = 0;
	cub->map = malloc(sizeof(char *) * 6);
	if (!cub->map)
		return (0);
	while (i < 6)
	{
		cub->map[i] = malloc(sizeof(char) * 6);
		if (!cub->map[i])
			return (0);
		i++;
	}
	cub->mlx = mlx_init(200, 200, "Basic window", 1);
	if (!cub->mlx)
		return (0);
	mlx_set_window_pos(cub->mlx, 750, 400);
	mlx_set_window_size(cub->mlx, WIDTH, HEIGHT);
	mlx_set_window_title(cub->mlx, "Cub3D");
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
	{
		mlx_delete_image(cub->mlx, cub->img);
		mlx_terminate(cub->mlx);
		return (0);
	}
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
	{
		mlx_delete_image(cub->mlx, cub->img);
		mlx_terminate(cub->mlx);
		return (0);
	}
	char buffer[1000];
	sprintf(buffer,"hi %f",mlx_get_time());
	cub->timer = mlx_put_string(cub->mlx,buffer,800,600);
	return 1;
}
