/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@stu	dent.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 10:48:59 by yrhandou          #+#    #+#             */
/*   Updated: 2025/09/07 10:13:09 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"

int main(int ac, char **av)
{
	t_cube cub;
	if (ac != 2)
	{
		write(2, "** Uncomplite Argument **\n", 27);
		exit(1000);
	}
	if (!cub_init(&cub, av[1]))
		return (1);
	draw_map(&cub);
	draw_plyr(&cub);
	// draw_bresenhamline(&cub,dest, YELLOW);
	mlx_key_hook(cub.mlx, handle_input, &cub);
	mlx_mouse_hook(cub.mlx, handle_mouse_events,&cub);
	mlx_close_hook(cub.mlx, ft_close, &cub);
	mlx_loop_hook(cub.mlx, draw_timer,&cub);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	return (0);
}
