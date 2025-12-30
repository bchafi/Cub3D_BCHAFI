/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:21:01 by bchafi            #+#    #+#             */
/*   Updated: 2025/12/29 03:45:52 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parcing.h"

char *multi_space(int len)
{
	char *line = malloc(len + 3);
	if (!line)
		return (NULL);
	int i = -1;
	while (++i < (len + 2))
		line[i] = ' ';
	line[i] = '\0';
	return (line);
}

int find_map_start(char **file)
{
	int i = 0;

	if (!file)
		return (-1);
	while (file[i])
	{
		char *trimed = ft_strtrim(file[i], " \t\n");
		if (!trimed)
			return (-1);
		if (*trimed && is_line_map(trimed))
		{
			free(trimed);
			return (i);
		}
		free(trimed);
		i++;
	}
	return (-1);
}

char **get_map(t_var *vars, char **file, int start)
{
	char **maping;
	int count;
	int i;
	int len;

	count = 0;
	i = start;
	while (file[i])
		(1) && (count++, i++);
	maping = malloc(sizeof(char *) * (count + 1));
	if (!maping)
		return (Error("Allocation Fail maping!!"), NULL);
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
	return (vars->map = maping, vars->lines_map = count, maping);
}

char **map_copy_s(t_var *var, char **map)
{
	int i, j;
	char **squer_map;
	int size = var->lines_map + 2;

	squer_map = malloc(sizeof(char *) * (size + 1));
	if (!squer_map)
		return (NULL);

	// Top line (walls)
	squer_map[0] = malloc(var->len_width + 3);
	memset(squer_map[0], '1', var->len_width + 2);
	squer_map[0][var->len_width + 2] = '\0';

	// Map lines
	for (i = 0; map[i]; i++)
	{
		squer_map[i + 1] = malloc(var->len_width + 3);
		memset(squer_map[i + 1], '1', var->len_width + 2); // default wall
		squer_map[i + 1][var->len_width + 2] = '\0';
		for (j = 0; map[i][j]; j++)
		{
			if (map[i][j] != ' ')
				squer_map[i + 1][j + 1] = map[i][j];
			else
				squer_map[i + 1][j + 1] = ' '; // keep space inside
		}
	}

	// Bottom line (walls)
	squer_map[i + 1] = malloc(var->len_width + 3);
	memset(squer_map[i + 1], '1', var->len_width + 2);
	squer_map[i + 1][var->len_width + 2] = '\0';

	squer_map[i + 2] = NULL;
	return squer_map;
}

int find_valid_map(t_var *vars)
{
	vars->map = get_map(vars, vars->read_file, vars->map_index);
	if (!vars->map)
		return (0);
	vars->map_s = map_copy_s(vars, vars->map);
	if (!vars->map_s)
	{
		free2D(vars->map);
		Error("Can't Squer the map!");
		return (0);
	}
	// here
	if (!validate_map(vars))
	{
		free2D(vars->map);
		free2D(vars->map_s);
		return (0);
	}
	return (1);
}
