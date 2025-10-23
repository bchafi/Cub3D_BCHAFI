/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_configure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:07:45 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/19 10:47:48 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parcing.h"

int check_tex(t_var *var, char *line)
{
    int		i;
	int		fd;
	char	*side;
	int		len_file;
	char	*path_img;

	(1) && (i = 2, side = ft_strndup(line, 3));
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    path_img = ft_strchr(line, line[i]);
    len_file = ft_strlen(path_img);
    if (len_file < 4 || ft_strcmp(path_img + len_file - 4, ".png") != 0)
        return (Error("Texture image must end with `.png`!"), free(side), 0);
    fd = open(path_img, O_RDONLY);
    if (fd < 0)
        return (Error("Texture image not found!"), free(side), 0);
    if (!ft_strcmp("NO ", side))
		var->NO = ft_strdup(path_img);
	if (!ft_strcmp("SO ", side))
		var->SO = ft_strdup(path_img);
	if (!ft_strcmp("EA ", side))
		var->EA = ft_strdup(path_img);
	if (!ft_strcmp("WE ", side))
		var->WE = ft_strdup(path_img);
    return (free(side), close(fd), 1);
}

int check_isnum(char *rgb_num)
{
	int i;

	i = 0;
	while (rgb_num[i])
	{
		if (rgb_num[i] < '0' || rgb_num[i] > '9')
			return (Error("Color RGB Not Number!"), 0);
		i++;
	}
	return (1);
}
int valide_Color(char **rgb)
{
	int i;

	i = 0;
	while (rgb[i])
	{
		char *slice = ft_strtrim(rgb[i], " ");
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

    var->tmp_r = ft_strtrim(slice_rgb[0], " \t\n");
    var->tmp_g = ft_strtrim(slice_rgb[1], " \t\n");
    var->tmp_b = ft_strtrim(slice_rgb[2], " \t\n");
    r = ft_atoi(var->tmp_r);
    g = ft_atoi(var->tmp_g);
    b = ft_atoi(var->tmp_b);
    free(var->tmp_r);
    free(var->tmp_g);
    free(var->tmp_b);
    (1) && (var->tmp_r = NULL, var->tmp_g = NULL, var->tmp_b = NULL);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (free2D(slice_rgb), Error("RGB values must be 0-255!"), 0);
    if (is_floor)
        var->floor_color = (r << 16) | (g << 8) | b;
    else
	{
        var->earth_color = (r << 16) | (g << 8) | b;
	}

	return (1);
}

int check_color(t_var *var, char *line, int is_floor)
{
	char	*side;
	char	*rgb_str;
	char	**slice_rgb;
	int		i;

	i = 1;
	side = ft_strndup(line, 2);
	if (!side)
		return (Error("Wrong RGB Color!!,), free(side)"), 0);
    while (line[i] == ' ' || line[i] == '\t')
	{
		i++;
	}
	rgb_str = ft_strdup(line + i);
	if (!rgb_str)
		return (Error("Wrong RGB Color!"), free(side), 0);
	slice_rgb = ft_split(rgb_str, ',', var);
	if (var->count_rgb != 3 || rgb_str[0] == ',')
	{
		Error("Error RGB Color `len`!");
		return (free(side), free(rgb_str), free2D(slice_rgb), 0);
	}
	if (!valide_Color(slice_rgb))
		return (free(side), free(rgb_str), free2D(slice_rgb), 0);
	
	if (!store_rgb(var, is_floor, slice_rgb))
		return (free(side), free(rgb_str), 0);
    return (free2D(slice_rgb), free(side), free(rgb_str), 1);
}

t_var *check_configuration(char **file_line, t_var *vars)
{
    int len = 0;
    int result;

    if (!initial_state(vars))
        return (NULL);
	
    result = check_file_lines(file_line, vars, &len);
    if (result == 0)
        return (free_textures(vars), NULL);
    if (result == 2)
    {
        // ft_printf(UGRN "configuration Is Ok.\n" reset);
        return (vars);
    }
    if (len != 6)
    {
        Error("Missing texture/color configuration 1");
        return (free_textures(vars), NULL);
    }
    return (vars);
}


    