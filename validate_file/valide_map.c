/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:21:01 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/19 11:58:54 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int is_valid_tile(char c)
{
	return (c == '0' || c == '1'
		|| c == 'N' || c == 'S'
		|| c == 'E' || c == 'W'
		|| c == ' ');
}

int check_surrounded(char **map, int i, int j)
{
	if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' ||
		map[i][j] == 'E' || map[i][j] == 'W')
	{
		if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
			map[i][j - 1] == ' ' || map[i][j + 1] == ' ' ||
			map[i - 1][j] == '\0' || map[i + 1][j] == '\0')
			return (0);
	}
	return (1);
}

int validate_walls(char **map)
{
	int i, j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_tile(map[i][j]))
				return (Error("Invalid char in map!"), 0);
			if (!check_surrounded(map, i, j))
				return (Error("Map not closed by walls!"), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int validate_map(t_var *var, char **map_s)
{
	(void)var;
	if (!validate_walls(map_s))
		return (0);

	return 1;
}