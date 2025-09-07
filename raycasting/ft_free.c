/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:44:37 by yrhandou          #+#    #+#             */
/*   Updated: 2025/09/06 14:35:56 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void free_arr(void **arr)
{
	int	i;

	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void free_player(t_player *plyr)
{
	plyr->direction = '\0';
	plyr->mapPosition.X =0;
	plyr->mapPosition.Y =0;
	// plyr->instancePosition->X = 0;
	// plyr->instancePosition->Y = 0;
	free(plyr);
}

void mlx_cleanup(t_cube *cub)
{
	free_arr((void **)cub->map);
	free_player(cub->plyr);
	mlx_close_window(cub->mlx);
}
