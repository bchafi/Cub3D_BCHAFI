/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:06:14 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/10 13:11:03 by bchafi           ###   ########.fr       */
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

void free2D(char **array)
{
	if (!*array || !array[0])
		return;
	while (*array != NULL)
	{
		free(*array);
		array++;
	}
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

int is_seeing(char **file_line, char *side, int end, int n)
{
	int i;

	i = -1;
	while (file_line[++i] && i < end)
	{
		if (!ft_strncmp(file_line[i], side, n))
			return (1);
	}
	return (0);
}

// ----------------------------
// Check Textures
// ----------------------------
int check_tex(t_var *var, char *line, char *side, t_kval *kval)
{
    int i = 2;

    if (line[i] != ' ' && line[i] != '\t')
        return (write(2, "Wrong LINE configuration!\n", 27), free(side), 0);

    while (line[i] == ' ' || line[i] == '\t')
        i++;

    char *path_img = ft_strchr(line, line[i]);
    kval[var->count].key = side;
    kval[var->count].value = ft_strdup(path_img);
    var->count++;
    return (1);
}

int check_isnum(char *rgb_num)
{
	int i;

	i = 0;
	while (rgb_num[i])
	{
		if (rgb_num[i] < 0 || rgb_num[i] > 9)
			return (0);
		i++;
	}
	return (1);
}

int check_color(t_var *var, char *line, char *side, t_kval *kval)
{
    int i = 1;

    if (line[i] != ' ' && line[i] != '\t')
        return (write(2, "Wrong RGB Color!!\n", 27), free(side), 0);

    while (line[i] == ' ' || line[i] == '\t')
        i++;
    char *path_img = ft_strchr(line, line[i]);
	char **slice_rgb = ft_split(ft_strdup(path_img), ',', var);
	if (var->count_rgb > 3)
	{
		write(2, "the Colors not correct!!\n", 26);
		return (free(path_img), free2D(slice_rgb), 0);
	}
	while (*slice_rgb)
	{
		*slice_rgb = ft_strtrim(*slice_rgb, " /n/t");
		if (!check_isnum(*slice_rgb))
			return (free(path_img), free2D(slice_rgb), 0);
		int num = ft_atoi(*slice_rgb);
		if(num >= 0 && ft_atoi(*slice_rgb) <= 255)
			slice_rgb++;
		else
		{
			write(2, "the Colors Range must `0-255`!!\n", 33);
			return (free(path_img), free2D(slice_rgb), 0);
		}
	}
    kval[var->count].key = side;
    kval[var->count].value = ft_strdup(path_img);
    var->count++;
    return (1);
}

t_var *initial_state(t_var *vars)
{
	int i;

	i = 0;
    vars->keyval = malloc(sizeof(t_kval) * 7);
    if (!vars->keyval)
        return (NULL);
	vars->count = 0;
	vars->count_rgb = 0;
	return (vars);
}

// ----------------------------
// Main check function
// ----------------------------
t_var *check_sides_tex(char **file_line, t_var *vars)
{
    int	i = 0;

	if (!initial_state(vars))
		return (NULL);
    while (file_line[i] != NULL)
    {	
        if (!ft_strncmp("NO ", file_line[i], 3) ||
            !ft_strncmp("SO ", file_line[i], 3) ||
            !ft_strncmp("WE ", file_line[i], 3) ||
            !ft_strncmp("EA ", file_line[i], 3))
        {
            if (is_seeing(file_line, file_line[i], i, 3))
                return (write(2, "Duplicate texture Direction!\n", 30), NULL);
            if (!check_tex(vars, file_line[i],
                    ft_strndup(file_line[i], 2), vars->keyval))
                return (NULL); // free(vars.keyval)
        }
		// -------
        else if (!ft_strncmp("F ", file_line[i], 2) ||
                 !ft_strncmp("C ", file_line[i], 2))
        {
            if (is_seeing(file_line, file_line[i], i, 2))
                return (write(2, "Duplicate color!\n", 17), NULL);

            if (!check_color(vars, file_line[i],
                    ft_strndup(file_line[i], 2), vars->keyval))
                return (NULL); // free(vars.keyval)
        }
        i++;
    }
    return vars;
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