/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray_casting_H.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:08:27 by sel-mir           #+#    #+#             */
/*   Updated: 2026/01/07 20:14:33 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		hold = (*data).ray_array[column_id[0]];
		(*(*hold).horizontal).x = coordinates[0];
		(*(*hold).horizontal).y = coordinates[1];
		(*(*hold).horizontal).angle = coordinates[2];
		(*(*hold).horizontal).distance = corrected_distance;
	}
	if (choice == VERTICAL)
	{
		hold = (*data).ray_array[column_id[0]];
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
