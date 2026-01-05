/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:06:14 by bchafi            #+#    #+#             */
/*   Updated: 2026/01/04 19:19:27 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parcing.h"

int check_isnum(char *rgb_num)
{
	int i;

	i = 0;
	while (rgb_num[i])
	{
		if (rgb_num[i] == '-')
			return (Error("Color RGB Must be Positive!"), 0);
		if (rgb_num[i] < '0' || rgb_num[i] > '9')
			return (Error("Color RGB Not Number!"), 0);
		i++;
	}
	return (1);
}

int check_file(char *arg)
{
	int	len;
	int	fd;

	len = ft_strlen(arg);
	if (len < 4 || ft_strcmp(arg + len - 4, ".cub") != 0)
	{
		Error("the file is not final `.cub`!!");
		return (-1);
	}
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		Error("the arg is a folder!!");
		close(fd);
		return (-1);
	}
	fd = open(arg, O_RDWR, 666);
	if (fd < 0)
	{
		Error("the file is not exist!!");
		return (-1);
	}
	return (fd);
}

char **get_full_file(int fd, char *arg, t_var *vars)
{
	char	*file;
	int		i;
	char	**file2D;

	(1) && (i = 0, file = get_next_line(fd));
	if (!file)
	{
		Error("the file is empty!!");
		return (close(fd), NULL);
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
