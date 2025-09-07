/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:09:01 by yrhandou          #+#    #+#             */
/*   Updated: 2025/09/07 11:51:48 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

t_player *set_PlyrPosition(char **map)
{
	int i;
	int j;
	t_player *plyr;
	t_vector worldPosition;

	plyr = ft_calloc(1, sizeof(t_player));
	if (!plyr)
		return (NULL);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_is_player(map[i][j]))
			{
				plyr->direction = map[i][j];
				update_vec(&plyr->mapPosition ,j, i);
				worldPosition = scaleToInstance(plyr->mapPosition);
				update_vec(&worldPosition ,worldPosition.X, worldPosition.Y);
				return (plyr);
			}
			j++;
		}
		i++;
	}
	return (plyr);
}

static void updateXaxis(t_cube *cub, int value, keys_t key)
{
	mlx_instance_t *PlyrPosition;
	t_vector newMapPos;
	t_vector newWorldPos;

	PlyrPosition = cub->plyr->instancePosition;
	if(key == MLX_KEY_RIGHT)
	{
		update_vec(&newWorldPos,PlyrPosition->x + value,PlyrPosition->y);
		newMapPos = scaleToMap(newWorldPos);
		if(mapCheck(cub, &newMapPos))
		{
			PlyrPosition->x += value;
			printf("new PlyrPosition RIGHT\n");
			print_vec((t_vector *)PlyrPosition);
		}
		else
			printf("BLOCKED BY WALL \n");
	}
	else if(key == MLX_KEY_LEFT)
	{
		update_vec(&newWorldPos,PlyrPosition->x - value,PlyrPosition->y);
		newMapPos = scaleToMap(newWorldPos);
		if(mapCheck(cub, &newMapPos))
		{
			PlyrPosition->x -= value;
			printf("new PlyrPosition LEFT\n");
			print_vec((t_vector *)PlyrPosition);
		}
		else
			printf("BLOCKED BY WALL \n");
	}
}

static void updateYaxis(t_cube *cub, int value, keys_t key)
{
	mlx_instance_t *PlyrPosition;
	t_vector newMapPos;
	t_vector newWorldPos;

	PlyrPosition = cub->plyr->instancePosition;
	if (key == MLX_KEY_UP)
	{
		update_vec(&newWorldPos,PlyrPosition->x, PlyrPosition->y - value);
		newMapPos = scaleToMap(newWorldPos);
		if(mapCheck(cub, &newMapPos))
		{
			PlyrPosition->y-= value;
			printf("new PlyrPosition UP\n");
			print_vec((t_vector *)PlyrPosition);
		}
		else
			printf("BLOCKED BY WALL \n");
	}
	if (key == MLX_KEY_DOWN)
	{
		update_vec(&newWorldPos,PlyrPosition->x, PlyrPosition->y + value);
		newMapPos = scaleToMap(newWorldPos);
		if(mapCheck(cub, &newMapPos))
		{
			PlyrPosition->y+= value;
			printf("new PlyrPosition DOWN\n");
			print_vec((t_vector *)PlyrPosition);
		}
		else
			printf("BLOCKED BY WALL \n");
	}
}

mlx_instance_t *update_plyrWinPos(t_cube *cub, int i, int j, keys_t key)
{
	mlx_instance_t *instPosition;

	instPosition = cub->plyr->instancePosition;
	if(key == MLX_KEY_RIGHT || key == MLX_KEY_LEFT)
		updateXaxis(cub, j, key);
	if(key == MLX_KEY_UP || key == MLX_KEY_DOWN)
		updateYaxis(cub, i, key);
	return (instPosition);
}
