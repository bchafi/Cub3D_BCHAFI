/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:21:01 by bchafi            #+#    #+#             */
/*   Updated: 2026/01/05 17:24:20 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parcing.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1'
		|| c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ');
}

int	check_validaion_maps(t_var *vars, int i, int j, char c)
{
	int	count;

	count = 0;
	if (!is_valid_char(c))
		return (error("Invalid character in map"), -1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		count++;
		vars->direction = c;
		vars->x = j;
		vars->y = i;
	}
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (vars->map_s[i - 1][j] == ' ' ||
			vars->map_s[i + 1][j] == ' ' ||
			vars->map_s[i][j - 1] == ' ' ||
			vars->map_s[i][j + 1] == ' ')
			return (error("Map not surrounded by walls"), -1);
	}
	return (count);
}

int	validate_map(t_var *vars)
{
	char	c;
	int		i;
	int		j;
	int		player_count;

	player_count = 0;
	i = 1;
	while (vars->map_s[i + 1])
	{
		j = 1;
		while (vars->map_s[i][j])
		{
			c = vars->map_s[i][j];
			if (check_validaion_maps(vars, i, j, c) == -1)
				return (0);
			player_count += check_validaion_maps(vars, i, j, c);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (error("Map must contain exactly one player"), 0);
	return (1);
}

char	**get_map(t_var *vars, char **file, int start)
{
	char	**maping;
	int		count;
	int		i;
	int		len;

	count = 0;
	i = start;
	while (file[i])
		(1) && (count++, i++);
	maping = malloc(sizeof(char *) * (count + 1));
	if (!maping)
		return (error("Allocation Fail maping!!"), NULL);
	i = 0;
	while (file[start] && start < vars->len_lines)
	{
		maping[i] = ft_strtrim(file[start], "\n");
		len = ft_strlen(maping[i]);
		if (vars->len_width < len)
			vars->len_width = len;
		(1) && (start++, i++);
	}
	maping[i] = NULL;
	vars->map = maping;
	vars->lines_map = count;
	return (maping);
}

void	free_partial_map(char **map, int i)
{
	while (i >= 0)
	{
		free(map[i]);
		i--;
	}
	free(map);
}
