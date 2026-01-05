/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:37:14 by sel-mir           #+#    #+#             */
/*   Updated: 2026/01/01 01:21:27 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_unit *da)
{
	t_unit	*data;

	data = holder(NULL);
	mlx_destroy_image((*data).mlx, (*data).img);
	mlx_destroy_window((*data).mlx, (*data).mlx_window);
	ft_free_alls(da->vars);
	ft_free(NULL, FREE_ALL);
}

void	texture_initiation(t_unit *data, t_var *map)
{
	char *files[] = {map->north, map->south, map->west, map->east};
	int a;

	a = 0;
	while (a < 4)
	{
		(*data).texture[a].texture_img = mlx_xpm_file_to_image((*data).mlx, files[a], &((*data).texture[a].width), &((*data).texture[a].height));
		if (!((*data).texture[a].texture_img))
		{
			ft_free_alls((*data).vars);	
			ft_free(NULL, FATAL);
		}
		(*data).texture[a].addr = mlx_get_data_addr((*data).texture[a].texture_img, 
			&((*data).texture[a].bpp), &((*data).texture[a].line_lenght), &((*data).texture[a].endian));
		if (!((*data).texture[a].addr))
		{
			ft_free_alls((*data).vars);				
			ft_free(NULL, FATAL);
		}
		a++;
	}
}

void	ray_casting_entry(t_var* map)
{
	t_unit	*data;
	int a = 0;
	
	data = ft_malloc(sizeof(t_unit));
	(*data).vars = map;
	(*data).map = map->map;
	(*data).celling_color = map->earth_color;
	(*data).floor_color = map->floor_color;
	(*data).mlx = mlx_init();
	(*data).ray = NULL;
	(*data).horizontal = NULL;
	(*data).vertical = NULL;
	holder(data);

	char_direction(data, (*map).direction);
	(*data).player_posx = (map->x * CUBE_DIM) + (CUBE_DIM / 2.0);
    (*data).player_posy = (map->y * CUBE_DIM) + (CUBE_DIM / 2.0);
	
	(*data).angle = (M_PI / 2);
	
	(*data).ray_tip_x = (*data).player_posx + 80 * cos((*data).angle);
	(*data).ray_tip_y = (*data).player_posy + 80 * sin((*data).angle);
	
	(*data).dir_vec_x = (*data).ray_tip_x - (*data).player_posx;
	(*data).dir_vec_y = (*data).ray_tip_y - (*data).player_posy;

	initiating(data);
	mlx_key_hook((*data).mlx_window, key_events, data);
	mlx_hook((*data).mlx_window, 17, 0, close_window, data);
	texture_initiation(data, map);
	free_textures(data);

	ray_inbulk(data);
	alpha(data, 0);
	mlx_loop((*data).mlx);
}

void	print_data(t_unit *data)
{
	int	a;
	t_ray	*head;

	head = (*data).ray;
	a = 0;
	while (head)
	{
		printf("\nRay:%d, ",a);
		printf("Vert_Inter:%f,%f , ", (*(*head).vertical).x,(*(*head).vertical).y);
		printf("Hori_Inter:%f,%f", (*(*head).horizontal).x,(*(*head).horizontal).y);
		a++;
		head = (*head).next;
	}
	printf("\n");
}
