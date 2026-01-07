/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 20:37:14 by sel-mir           #+#    #+#             */
/*   Updated: 2026/01/07 21:27:57 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(void)
{
	t_unit	*data;

	data = holder(NULL);
	mlx_destroy_image((*data).mlx, (*data).img);
	mlx_destroy_window((*data).mlx, (*data).mlx_window);
	ft_free(NULL, FREE_ALL);
	return (0);
}

char	**set_files(t_var *s)
{
	char	**files;

	files = ft_malloc(sizeof(char *) * 4);
	files[0] = s->north;
	files[1] = s->south;
	files[2] = s->west;
	files[3] = s->east;
	return (files);
}

void	texture_initiation(t_unit *data)
{
	char	**files;
	int		a;

	a = 0;
	files = set_files(data->map_s);
	while (a < 4)
	{
		(*data).texture[a].texture_img = mlx_xpm_file_to_image((*data).mlx,
				files[a], &((*data).texture[a].width),
				&((*data).texture[a].height));
		if (!((*data).texture[a].texture_img))
			ft_free(NULL, FATAL);
		(*data).texture[a].addr = mlx_get_data_addr(
				(*data).texture[a].texture_img,
				&((*data).texture[a].bpp),
				&((*data).texture[a].line_lenght),
				&((*data).texture[a].endian));
		if (!((*data).texture[a].addr))
			ft_free(NULL, FATAL);
		a++;
	}
}

void	get_stuff_ready(t_unit *data, char **new, t_var *map)
{
	lenght_of_map(new, data);
	(*data).view_angle = (60.0 * (M_PI / 180.0));
	(*data).ang_between_rays = ((*data).view_angle / WIDTH);
	(*data).proj_plane_dist = ((WIDTH / 2.0) / tan((*data).view_angle / 2.0));
	(*data).map_s = map;
	(*data).map = new;
	(*data).ray = NULL;
	(*data).horizontal = NULL;
	(*data).vertical = NULL;
	holder(data);
	char_direction(data, (*map).direction);
	(*data).player_posx = ((*map).x * CUBE_DIM) + (CUBE_DIM / 2.0);
	(*data).player_posy = ((*map).y * CUBE_DIM) + (CUBE_DIM / 2.0);
	(*data).ray_tip_x = (*data).player_posx + 80 * cos((*data).angle);
	(*data).ray_tip_y = (*data).player_posy + 80 * sin((*data).angle);
	(*data).dir_vec_x = (*data).ray_tip_x - (*data).player_posx;
	(*data).dir_vec_y = (*data).ray_tip_y - (*data).player_posy;
}

void	ray_casting_entry(t_var *map, char **new)
{
	t_unit	*data;

	data = ft_malloc(sizeof(t_unit));
	get_stuff_ready(data, new, map);
	initiating(data);
	
    mlx_hook((*data).mlx_window, 2, 1L<<0, key_press, data);
    mlx_hook((*data).mlx_window, 3, 1L<<1, key_release, data);
    mlx_hook((*data).mlx_window, 17, 0, close_window, data);
    mlx_loop_hook((*data).mlx, update_loop, data);
	texture_initiation(data);
	free_textures(data);
	ray_inbulk(data);
	alpha(data, 0);
	mlx_loop((*data).mlx);
}
