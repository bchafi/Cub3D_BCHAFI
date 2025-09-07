/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_actor_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:49:20 by yrhandou          #+#    #+#             */
/*   Updated: 2025/09/07 15:49:27 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// -----------



// -----------


static mlx_instance_t *set_plyrInstancePos(t_player *plyr, mlx_instance_t *inst)
{
	t_vector worldPos;

	worldPos = scaleToInstance(plyr->mapPosition);
	inst->x = worldPos.X;
	inst->y = worldPos.Y;
	return (inst);
}

t_player *set_playerPosition(char **map)
{
	int i;
	int j;
	t_player *plyr;

	plyr = ft_calloc(1, sizeof(t_player));
	if (!plyr)
		return NULL;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_is_player(map[i][j]))
			{
				plyr->mapPosition.X = j;
				plyr->mapPosition.Y = i;
				break;
			}
			j++;
		}
		i++;
	}
	plyr->direction = map[plyr->mapPosition.Y][plyr->mapPosition.X];
	return plyr;
}


char **set_map(void)
{
	int i;
	char **map;
	i = 0;
	char *maap[] = {
		"111111111111111111111",
		"1N1100001110000000001",
		"100000000000000000001",
		"111110000000000000001",
		"110010000000010000001",
		"100000000011000001001",
		"111111111111111111111",
		NULL};
	map = ft_calloc(8, sizeof(char *));
	if (!map)
		return (0);
	while (maap[i])
	{
		map[i] = ft_strdup(maap[i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}

void init_timer(t_cube *cub)
{
	char buffer[1000];
	sprintf(buffer, "%f", mlx_get_time());
	cub->timer = mlx_put_string(cub->mlx, buffer, 800, 600);
	cub->hide_timer = 0;
}

t_player *init_playerData(t_cube *cub)
{
	t_player	*plyr;

	plyr = set_playerPosition(cub->map);
	if(!plyr)
		return (NULL);
	cub->PlyrImg = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if(!cub->PlyrImg)
		return free_player(plyr), (NULL);
	plyr->inst = mlx_image_to_window(cub->mlx, cub->PlyrImg, 0, 0);
	if(plyr->inst == -1)
	{
		mlx_delete_image(cub->mlx, cub->PlyrImg);
		free(plyr);
		return (NULL);
	}
	plyr->instancePosition = set_plyrInstancePos(plyr, cub->PlyrImg->instances);
	if(!plyr->instancePosition)
	{
		mlx_delete_image(cub->mlx, cub->PlyrImg);
		free_player(plyr);
		return (NULL);
	}
	return (plyr);
}

static int init_mapData(t_cube *cub, int fd)
{
	cub->map = set_map();
	cub->map = parsing_map(fd);
	if(!cub->map)
		return (0);
	// char *line;
	// while ((line = get_next_line(fd)))
	// {
	// 	printf("%s", line);
	// 	free(line);
	// }
	cub->MapImg = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->MapImg)
		return (free_arr((void **)cub->map), 0);
	if (mlx_image_to_window(cub->mlx, cub->MapImg, 0, 0) == -1)
	{
		mlx_delete_image(cub->mlx, cub->MapImg);
		return (free_arr((void **)cub->map), 0);
	}
	return (1);
}

int	check_file(char *arg)
{
	int	len;
	int	fd;

	len = ft_strlen(arg);
	if (len < 4 || ft_strcmp(arg + len - 4, ".cub") != 0)
	{
		write(2, "the file is not final `.cub`.\n", 31);
		exit(1001);
	}
	fd = open(arg, O_DIRECTORY, 666);
	if (fd >= 0)
	{
		close(fd);
		write(2, "the arg is a folder.\n", 22);
		exit(1002);
	}
	fd = open(arg, O_RDWR, 666);
	if (fd < 0)
	{
		write(2, "the file is not exist.\n", 24);
		exit(1002);
	}
	return (fd);
}

int cub_init(t_cube *cub, char *arg)
{
	int fd = check_file(arg);
	cub->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", 1);
	if (!cub->mlx)
		return (0);
	if(!init_mapData(cub, fd))
		return (mlx_terminate(cub->mlx), 0);
	cub->plyr = init_playerData(cub);
	if (!cub->plyr)
	{
		mlx_delete_image(cub->mlx, cub->MapImg);
		free_arr((void **)cub->map);
		mlx_terminate(cub->mlx);
		return (0);
	}
	mlx_set_window_pos(cub->mlx, 750, 400);
	init_timer(cub);
	return (1);
}
