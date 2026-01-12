/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:11:17 by sel-mir           #+#    #+#             */
/*   Updated: 2026/01/07 22:22:31 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	find_vertical_intersection(t_unit *data, t_geometrie geom)
{
	t_calcul	calcul;

	if (geom.ray_vec_x == 0)
		return (set_ray(data, VERTICAL,
				(float []){-1, -1, -1}, geom.column_id), (void)0);
	intial_vert(data, geom.ray_vec_x, geom.ray_vec_y,
		(float *[]){&(calcul.x_v), &(calcul.y_v), &(geom.angle)});
	if (geom.ray_vec_x < 0)
		calcul.x_i = -CUBE_DIM;
	else
		calcul.x_i = CUBE_DIM;
	calcul.y_i = calcul.x_i * (geom.ray_vec_y / geom.ray_vec_x);
	find_vertical_rest(calcul, geom, data);
}

int	intial_vert(t_unit *data, float ray_vec_x,
		float ray_vec_y, float *coordi[3])
{
	float	x_v;
	float	y_v;
	float	dx;
	float	dy;

	if (ray_vec_x < 0)
		x_v = ((int)(data->player_posx / CUBE_DIM) * CUBE_DIM);
	else
		x_v = ((int)(data->player_posx / CUBE_DIM) * CUBE_DIM) + CUBE_DIM;
	dx = x_v - (*data).player_posx;
	dy = dx * (ray_vec_y / ray_vec_x);
	y_v = (*data).player_posy + dy;
	*coordi[0] = x_v;
	*coordi[1] = y_v;
	return (YES);
}

void	create_ray_rest(t_unit *data, t_intersection *vertical,
			t_intersection *horizontal, int id)
{
	t_ray	*head;
	t_ray	*hold;

	head = (*data).ray;
	while (head)
	{
		hold = head;
		head = (*head).next;
	}
	(*hold).next = ft_malloc(sizeof(t_ray));
	head = (*hold).next;
	(*head).id = id;
	(*head).next = NULL;
	(*head).horizontal = horizontal;
	(*head).horizontal->is_vertical = 0;
	(*head).vertical = vertical;
	(*head).vertical->is_vertical = 1;
	(*head).nearest = smallest((*head).vertical, (*head).horizontal);
	(*data).ray_array[id] = head;
}

void	create_ray(t_unit *data, t_intersection *vertical,
			t_intersection *horizontal, int id)
{
	static int	flag;
	t_ray		*head;

	if (!flag)
		(*data).ray_array = ft_malloc(sizeof(t_ray) * WIDTH);
	flag++;
	if (!(*data).ray)
	{
		(*data).ray = ft_malloc(sizeof(t_ray));
		head = (*data).ray;
		(*head).next = NULL;
		(*head).id = id;
		(*head).horizontal = horizontal;
		(*head).horizontal->is_vertical = 0;
		(*head).vertical = vertical;
		(*head).vertical->is_vertical = 1;
		(*head).nearest = smallest((*head).vertical, (*head).horizontal);
		(*data).ray_array[id] = (*data).ray;
		return ;
	}
	create_ray_rest(data, vertical, horizontal, id);
}

//	This Function Looks for the strcut that has the same pointer passed
//	to it and returns the struct 

void	search_gcollct(t_gcollct *head, void *ptr, t_gcollct **ret)
{
	t_gcollct	*before;
	t_gcollct	*next;

	next = NULL;
	before = NULL;
	while (head)
	{
		if ((*head).ptr == ptr)
		{
			ret[0] = before;
			ret[1] = head;
			ret[2] = next;
			return ;
		}
		before = head;
		head = (*head).next;
		if (head)
			next = (*head).next;
		else if (!head)
			next = NULL;
	}
}
