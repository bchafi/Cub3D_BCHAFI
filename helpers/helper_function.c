/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HelperFunction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:03:23 by sel-mir           #+#    #+#             */
/*   Updated: 2026/01/07 22:22:58 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_ifwall(t_unit *data, int x, int y)
{
	int	gx;
	int	gy;

	if (x < 0 || y < 0)
		return (YES);
	gx = x / CUBE_DIM;
	gy = y / CUBE_DIM;
	if (gy < 0 || gy >= data->maplinemax)
		return (YES);
	if (gx < 0 || gx >= data->lenght_line_map[gy])
		return (YES);
	if (data->map[gy][gx] == '1' || data->map[gy][gx] == ' '
			|| data->map[gy][gx] == '\0')
		return (YES);
	return (NO);
}

void	lenght_of_map(char **map, t_unit *data)
{
	int	a;
	int	i;

	a = 0;
	while (map[a])
		a++;
	data->maplinemax = a;
	data->lenght_line_map = ft_malloc(sizeof(int) * a);
	a = 0;
	while (map[a])
	{
		i = 0;
		while (map[a][i])
			i++;
		data->lenght_line_map[a] = i;
		a++;
	}
}
