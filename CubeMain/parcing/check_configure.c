/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_configure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:07:45 by bchafi            #+#    #+#             */
/*   Updated: 2026/01/05 08:18:21 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parcing.h"

int	check_tex(t_var *var, char *line)
{
	int		i;
	int		fd;
	char	*side;
	char	*path_img;

	(1) && (i = 2, side = ft_strndup(line, 3));
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	path_img = ft_strdup(ft_strchr(line, line[i]));
	if (ft_strlen(path_img) < 4
		|| ft_strcmp(path_img + ft_strlen(path_img) - 4, ".xpm") != 0)
		return (Error("Texture must end with .xpm"),
			free(path_img), free(side), 0);
	fd = open(path_img, O_RDONLY);
	if (fd < 0)
		return (Error("Texture not found"), free(path_img), free(side), 0);
	if (!ft_strcmp("NO ", side))
		var->north = path_img;
	else if (!ft_strcmp("SO ", side))
		var->south = path_img;
	else if (!ft_strcmp("EA ", side))
		var->east = path_img;
	else if (!ft_strcmp("WE ", side))
		var->west = path_img;
	return (free(side), close(fd), 1);
}

int valide_Color(char **rgb)
{
	int		i;
	char	*slice;

	i = 0;
	while (rgb[i])
	{
		slice = ft_strtrim(rgb[i], " ");
		if (!check_isnum(slice))
			return (free(slice), 0);
		free(slice);
		slice = NULL;
		i++;
	}
	return (1);
}

int store_rgb(t_var *var, int is_floor, char **slice_rgb)
{	
	int     r;
    int     g;
    int     b;

	var->tmp_a = ft_strtrim(slice_rgb[0], " \t\n");
	var->tmp_b = ft_strtrim(slice_rgb[1], " \t\n");
	var->tmp_c = ft_strtrim(slice_rgb[2], " \t\n");
	if (!var->tmp_a || !var->tmp_b || !var->tmp_c)
		return (Error("Memory Allocation RGB Failed!"), 0);	
    r = ft_atoi(var->tmp_a);
    g = ft_atoi(var->tmp_b);
    b = ft_atoi(var->tmp_c);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (free(var->tmp_a), free(var->tmp_b), free(var->tmp_c), Error("RGB values must be 0-255!"), 0);
    if (is_floor)
        var->floor_color = (r << 16) | (g << 8) | b;
    else
	{
        var->earth_color = (r << 16) | (g << 8) | b;
	}
	free(var->tmp_a);
	free(var->tmp_b);
	free(var->tmp_c);
	return (1);
}

int check_color(t_var *var, char *line, int is_floor)
{
	char	*rgb_str;
	char	**slice_rgb;
	int		i;

	i = 1;
    while (line[i] == ' ' || line[i] == '\t')
		i++;
	rgb_str = ft_strdup(line + i);
	if (!rgb_str)
		return (Error("Wrong RGB Color!"), 0);
	slice_rgb = ft_split(rgb_str, ',', var);
	if (!slice_rgb)
		return (free(rgb_str), Error("Wrong RGB Color Split!"), 0);
	if (var->count_rgb != 3 || rgb_str[0] == ',')
	{
		Error("Error RGB Color `len`!");
		return (free(rgb_str), free2D(slice_rgb), 0);
	}
	if (!valide_Color(slice_rgb))
		return (free(rgb_str), free2D(slice_rgb), 0);
	if (!store_rgb(var, is_floor, slice_rgb))
		return (free2D(slice_rgb), free(rgb_str), 0);
    return (free2D(slice_rgb), free(rgb_str), 1);
}

t_var *check_configuration(char **file_line, t_var *vars)
{
    int	len;
    int	result;

	len = 0;
    if (!initial_state(vars))
        return (NULL);
	
    result = check_file_lines(file_line, vars, &len);
    if (result == 0)
        return (NULL);
    if (result == 2)
        return (vars);
    if (len != 6)
    {
        Error("Missing texture/color configuration 1");
        return (NULL);
    }
    return (vars);
}


    