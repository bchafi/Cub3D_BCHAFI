/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:06:14 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/12 10:03:36 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int check_file(char *arg)
{
	int len;
	int fd;

	len = ft_strlen(arg);
	if (len < 4 || ft_strcmp(arg + len - 4, ".cub") != 0)
	{
		write(2, "the file is not final `.cub`.\n", 31);
		exit(1001);
	}
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		write(2, "the arg is a folder.\n", 22);
		close(fd);
		exit(1002);
	}
	fd = open(arg, O_RDWR, 666);
	if (fd < 0)
	{
		write(2, "the file is not exist.\n", 24);
		exit(1002);
	}
	return (fd);
}
void read2D(char **array, int len)
{
	int i;

	i = 0;
	if (!array[i] || !array)
		return;
	while (array[i] != NULL && i < len)
	{
		printf("%s", array[i]);
		i++;
	}
}
char **get_map(int fd, char *arg, t_var *vars)
{
	char *file;
	int i;
	char **file2D;

	(1) && (i = 0, file = get_next_line(fd));
	if (!file)
	{
		close(fd);
		write(2, "** the file is empty **\n", 24);
		return (NULL);
	}
	while (file)
		(1) && (free(file), i++, file = get_next_line(fd));
	file2D = (char **)malloc(sizeof(char *) * (i + 1));
	if (!file2D)
		return (close(fd), NULL);
	(1) && (close(fd), fd = open(arg, O_RDONLY), i = 0);
	if (fd < 0)
		return (free(file2D), NULL);
	file = get_next_line(fd);
	while (file)
		(1) && (file2D[i++] = file, file = get_next_line(fd));
	(1) && (file2D[i] = NULL);
	return (close(fd), vars->line_lines = i, file2D);
}
void free2D(char **array)
{
    int i;

	i = 0;

    if (!array)
        return;
    while (array[i])
	{
        free(array[i]);
		i++;	
	}
    free(array);
}


void free_textures(t_var *vars)
{
	// printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", vars->NO, vars->SO, vars->WE, vars->EA);
	free(vars->NO);
	vars->NO = NULL;
	free(vars->SO);
	vars->SO = NULL;
	free(vars->WE);
	vars->WE = NULL;
	free(vars->EA);
	vars->EA = NULL;
}
t_var *initial_state(t_var *vars)
{
	vars->count_rgb = 0;
	vars->NO = ft_strdup("");
	vars->SO = ft_strdup("");
	vars->WE = ft_strdup("");
	vars->EA = ft_strdup("");
	vars->map_index = -1;
	return (vars);
}
int is_line_map(char *file_line)
{
    int i;

	i = 0;
    while (file_line[i])
    {
        if (file_line[i] == '0' || file_line[i] == '1'
			|| file_line[i] == ' ' || file_line[i] == '\t')
            i++;
        else
            return (0);
    }
    return (1);
}
int is_seeing(char **file_line, char *side, int end, int n)
{
	int i;

	i = -1;
	while (file_line[++i] && i < end)
	{
		char *trimed = ft_strtrim(file_line[i], " \n\t");
		if (!ft_strncmp(trimed, side, n))
			return (free(trimed), 1);
		free(trimed);
	}
	return (0);
}
// ----------------------------
// Check Textures
// ----------------------------
int check_tex(t_var *var, char *line)
{
    int i;
	char *side;
	
	i = 2;
	side = ft_strndup(line, 3);
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    char *path_img = ft_strchr(line, line[i]);
    int len_file = ft_strlen(path_img);
    if (len_file < 4 || ft_strcmp(path_img + len_file - 4, ".png") != 0)
        return (write(2, "Texture image must end with `.png`!!\n", 37), free(side), 0);
    int fd = open(path_img, O_RDONLY);
    if (fd < 0)
        return (write(2, "Texture image not found!!\n", 27), free(side), 0);
    close(fd);
    if (!ft_strcmp("NO ", side))
		var->NO = ft_strdup(path_img);
    if (!ft_strcmp("SO ", side))
		var->SO = ft_strdup(path_img);
    if (!ft_strcmp("WE ", side))
		var->WE = ft_strdup(path_img);
    if (!ft_strcmp("EA ", side))
		var->EA = ft_strdup(path_img);
	free(side);
    return (1);
}

// -----------------------------------------

int check_isnum(char *rgb_num)
{
	int i;

	i = 0;
	while (rgb_num[i])
	{
		if (rgb_num[i] < '0' || rgb_num[i] > '9')
			return (write(2, "Color RGB Not Number!!\n", 24), 0);
		i++;
	}
	return (1);
}
int valide_Color(char **rgb)
{
	int i;
	int j;


	i = 0;
	while (rgb[i])
	{
		j = 0;
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
	int r, g, b;
	char *tmp_r = ft_strtrim(slice_rgb[0], " \t\n");
    char *tmp_g = ft_strtrim(slice_rgb[1], " \t\n");
    char *tmp_b = ft_strtrim(slice_rgb[2], " \t\n");

    r = ft_atoi(tmp_r);
    g = ft_atoi(tmp_g);
    b = ft_atoi(tmp_b);
    free(tmp_r);
    free(tmp_g);
    free(tmp_b);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free2D(slice_rgb);
        return (write(2, "RGB values must be 0-255!!\n", 28), 0);
	}
    if (is_floor)
        var->floor_color = (r << 16) | (g << 8) | b;
    else
        var->earth_color = (r << 16) | (g << 8) | b;
	return (1);
}

// ----------------------------
// Check Colors
// ----------------------------
int check_color(t_var *var, char *line, int is_floor)
{
	char	*side;
	char	*rgb_str;
	char	**slice_rgb;
	int		i;

	i = 1;
	side = ft_strndup(line, 2);
	if (!side)
		return (write(2, "Wrong RGB Color!!\n", 19), free(side), 0);
    while (line[i] == ' ' || line[i] == '\t')
        i++;
	rgb_str = ft_strdup(line + i);
	if (!rgb_str)
		return (write(2, "Wrong RGB Color!!\n", 19), free(side), 0);
	slice_rgb = ft_split(rgb_str, ',', var);
	if (var->count_rgb != 3 || rgb_str[0] == ',')
	{
		write(2, "Error RGB Color `len`!!\n", 25);
		return (free(side), free(rgb_str), free2D(slice_rgb), 0);
	}
	if (!valide_Color(slice_rgb))
		return (free(side), free(rgb_str), free2D(slice_rgb), 0);
	
	if (!store_rgb(var, is_floor, slice_rgb))
		return (free(side), free(rgb_str), 0);
    free2D(slice_rgb);
	free(side);
	free(rgb_str);
    return (1);
}




// ----------------------------
// Main check function
// ----------------------------
t_var *check_sides_tex(char **file_line, t_var *vars)
{
    int	i = 0;
	int len = 0;

	if (!initial_state(vars))
		return (NULL);
	// printf("== TEXTURES | COLORS==\n");
    while (file_line[i] != NULL)
    {	
		char *trimed = ft_strtrim(file_line[i], " \n\t");
		if (!trimed || !*trimed)
        {
            free(trimed);
			free_textures(vars);
            i++;
            continue;
        }
		if (is_line_map(trimed))
		{
			if (len != 6)
				write(2, "Missing texture/color configuration1!\n", 38);return (free(trimed), vars->map_index = i, vars);
			
			free(trimed);
			free_textures(vars);
			return (NULL);			
		}
        else if (!ft_strncmp("NO ", trimed, 3) ||
            !ft_strncmp("SO ", trimed, 3) ||
            !ft_strncmp("WE ", trimed, 3) ||
            !ft_strncmp("EA ", trimed, 3))
        {
            if (is_seeing(file_line, trimed, i, 3) || file_line[i][0] == ' ')
			{
				write(2, "Errpr\n: Duplicate texture/color configuration2!\n", 40);
				free(trimed);
				free_textures(vars);
                return (NULL);
			}
            if (!check_tex(vars, trimed))
			{
				free(trimed);
				free_textures(vars);
                return (NULL);
			}
			len++;
        }
        else if (!ft_strncmp("F ", trimed, 2) ||
                 !ft_strncmp("C ", trimed, 2))
        {
            if (is_seeing(file_line, trimed, i, 2) || file_line[i][0] == ' ')
			{
				write(2, "texture/color configuration3!!\n", 31);
				free(trimed);
				free_textures(vars);
                return (NULL);
			}
            else if (!ft_strncmp("F ", trimed, 2))
			{
				if (!check_color(vars, trimed, 1))
					return (free(trimed), free_textures(vars), NULL);
			}
			else if (!ft_strncmp("C ", trimed, 2))
			{
				if (!check_color(vars, trimed, 0))
					return (free(trimed), free_textures(vars), NULL);
			}
			len++;
        }
		else if (ft_isalpha(trimed[0]))
			return (free(trimed), free_textures(vars), write(2, "Line Configuration Wrong!!\n", 28), NULL);
		free(trimed);
		i++;
    }
	if (len != 6)
    {
        write(2, "Missing texture/color configuration!\n", 37);
        return (free_textures(vars), NULL);
    }
    return (vars);
}

// t_var *check_texturs(char *arg, t_var *var)
// {
// 	char *str;

// 	if (!ft_strncmp(arg, "NO ", 3))
// 		var->no = ft_strchr(arg, " ");
// 	else if (!ft_strncmp(arg, "SO ", 3))
// 		var->so = ft_strchr(arg, " ");
// 	else if (!ft_strncmp(arg, "WE ", 3))
// 		var->we = ft_strchr(arg, " ");
// 	else if (!ft_strncmp(arg, "EA ", 3))
// 		var->ea = ft_strchr(arg, " ");
// 	else if (!ft_strncmp(arg, "F ", 3))
// 		var->f = ft_strchr(arg, " ");
// 	else if (!ft_strncmp(arg, "C ", 3))
// 		var->c = ft_strchr(arg, " ");
	
// 	return (var);
// }