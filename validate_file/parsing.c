/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:06:14 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/17 15:22:38 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void Error(char *str)
{
	ft_printf(RED URED BHRED);
	write(2,"## Error\n##", 12);
	write(2, str, ft_strlen(str));
	ft_printf(" ##"reset);
	write(2,"\n", 1);
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

int check_file(char *arg)
{
	int len;
	int fd;

	len = ft_strlen(arg);
	if (len < 4 || ft_strcmp(arg + len - 4, ".cub") != 0)
	{
		Error("the file is not final `.cub`!!");
		exit(1001);
	}
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		Error("the arg is a folder!!");
		close(fd);
		exit(1002);
	}
	fd = open(arg, O_RDWR, 666);
	if (fd < 0)
	{
		Error("the file is not exist!!");
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

char **get_full_file(int fd, char *arg, t_var *vars)
{
	char *file;
	int i;
	char **file2D;

	(1) && (i = 0, file = get_next_line(fd));
	if (!file)
	{
		close(fd);
		Error("the file is empty!!");
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
	file2D[i] = NULL;
	return (close(fd), vars->len_lines = i, file2D);
}
