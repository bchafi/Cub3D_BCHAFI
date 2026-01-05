/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray_casting_H.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:08:27 by sel-mir           #+#    #+#             */
/*   Updated: 2026/01/01 00:08:56 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_ifwall(t_unit *data, int x, int y)
{
	int	gx;
	int	gy;
	int	i;
	char **map;

	i = 0;
	map = (*data).map;
	gx = x / CUBE_DIM;
    gy = y / CUBE_DIM;
	
	while (map[i])
		i++;
	if (gy < 0 || gy >= i)
        return YES;
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
	
	while ( a <= WIDTH)
	{
		t_intersection *horiz = ft_malloc(sizeof(t_intersection));
		t_intersection *vert = ft_malloc(sizeof(t_intersection));
		create_ray(data, vert, horiz, a);
		a++;
	}
}

void	set_ray(t_unit *data, int choice, float coordinates[3], int column_id)
{
	t_ray	*hold;
    float   raw_distance;
    float   corrected_distance;

	corrected_distance = FLT_MAX;
	hold = NULL;
	if (coordinates[0] != -1 && coordinates[1] != -1)
	{
		raw_distance = sqrtf(
			(coordinates[0] - (*data).player_posx) * (coordinates[0] - (*data).player_posx) +
			(coordinates[1] - (*data).player_posy) * (coordinates[1] - (*data).player_posy));
			
		corrected_distance = raw_distance * cos(coordinates[2] - (*data).angle);
	}
	if (choice == HORIZONTAL)
	{
		hold = find_ray_byid(data, column_id);
		(*(*hold).horizontal).x = coordinates[0];
		(*(*hold).horizontal).y = coordinates[1];
		(*(*hold).horizontal).angle = coordinates[2];
		(*(*hold).horizontal).distance = corrected_distance;
	}
	if (choice == VERTICAL)
	{
		hold = find_ray_byid(data, column_id);
		(*(*hold).vertical).x = coordinates[0];
		(*(*hold).vertical).y = coordinates[1];
		(*(*hold).vertical).angle = coordinates[2];
		(*(*hold).vertical).distance = corrected_distance;
		(*hold).nearest = smallest((*hold).vertical, (*hold).horizontal);
	}
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

t_unit	*holder(t_unit *data)
{
	static	t_unit	*precious;

	if (!precious)
		precious = data;
	return (precious);
}