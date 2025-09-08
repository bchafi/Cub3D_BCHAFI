/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:06:14 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/08 10:15:55 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_file(char *arg)
{
	int	len;
	int	fd;

	len = ft_strlen(arg);
	if (len < 4 || ft_strcmp(arg + len - 4, ".cub") != 0)
	{
		write(2, "the file is not final `.cub`.\n", 31);
		exit(1001);
	}
	fd = open(arg, O_DIRECTORY, 666);
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

void free2D(void **array)
{
    if (!*array || !array)
        return;
    while (*array)
    {
        free(*array);
        array++;
    }    
}

char	**get_map(int fd, char *arg, t_var *vars)
{
	char	*file;
	int		i;
	char	**file2D;

	(1) && (i = 0, file = get_next_line(fd));
	if (!file)
	{
		close(fd);
		write(2, "** the file is empty **\n", 24);
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
	return (close(fd));
}
