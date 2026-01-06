/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray_casting_H.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:08:27 by sel-mir           #+#    #+#             */
/*   Updated: 2026/01/06 08:28:37 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_ifwall(t_unit *data, int x, int y)
{
	char	**map;
	int		gx;
	int		gy;
	int		i;

	i = 0;
	map = (*data).map;
	gx = x / CUBE_DIM;
	gy = y / CUBE_DIM;
	while (map[i])
		i++;
	if (gy < 0 || gy >= i)
		return (YES);
	i = 0;
	while (map[gy][i])
		i++;
	if ((gx < 0 || gx >= i))
		return (YES);
	if ((*data).map[gy][gx] == '1' || (*data).map[gy][gx] == ' ')
		return (YES);
	return (NO);
}

void	ray_inbulk(t_unit *data)
{
	int	a;

	a = 0;
	while (a < WIDTH)
	{
		create_ray(data, ft_malloc(sizeof(t_intersection)),
			ft_malloc(sizeof(t_intersection)), a);
		a++;
	}
}

void	set_ray_rest(float corrected_distance,
		t_unit *data, int column_id[2], float coordinates[3])
{
	t_ray	*hold;
	int		choice;

	choice = column_id[1];
	hold = NULL;
	if (choice == HORIZONTAL)
	{
		hold = find_ray_byid(data, column_id[0]);
		(*(*hold).horizontal).x = coordinates[0];
		(*(*hold).horizontal).y = coordinates[1];
		(*(*hold).horizontal).angle = coordinates[2];
		(*(*hold).horizontal).distance = corrected_distance;
	}
	if (choice == VERTICAL)
	{
		hold = find_ray_byid(data, column_id[0]);
		(*(*hold).vertical).x = coordinates[0];
		(*(*hold).vertical).y = coordinates[1];
		(*(*hold).vertical).angle = coordinates[2];
		(*(*hold).vertical).distance = corrected_distance;
		(*hold).nearest = smallest((*hold).vertical, (*hold).horizontal);
	}
}

void	set_ray(t_unit *data, int choice, float coordinates[3], int column_id)
{
	float	raw_distance;
	float	corrected_distance;

	corrected_distance = FLT_MAX;
	if (coordinates[0] != -1 && coordinates[1] != -1)
	{
		raw_distance = sqrtf(
				(coordinates[0] - (*data).player_posx)
				* (coordinates[0] - (*data).player_posx)
				+ (coordinates[1] - (*data).player_posy)
				* (coordinates[1] - (*data).player_posy));
		corrected_distance = raw_distance * cos(coordinates[2] - (*data).angle);
	}
	set_ray_rest(corrected_distance, data,
		(int []){column_id, choice}, coordinates);
}

t_ray	*find_ray_byid(t_unit *data, int id)
{
	t_ray	*head;

	head = (*data).ray;
	while (head)
	{
		if ((*head).id == id)
			return (head);
		head = (*head).next;
	}
	return (NULL);
}
