/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:06:14 by bchafi            #+#    #+#             */
/*   Updated: 2026/01/11 14:30:04 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parcing.h"

int	check_isnum(char *rgb_num)
{
	int	i;

	i = 0;
	while (rgb_num[i])
	{
		if (rgb_num[i] == '-')
			return (error("Color RGB Must be Positive!"), 0);
		if (rgb_num[i] < '0' || rgb_num[i] > '9')
			return (error("Color RGB Not Number!"), 0);
		i++;
	}
	return (1);
}

int	check_file(char *arg)
{
	int	len;
	int	fd;

	len = ft_strlen(arg);
	if (len < 4 || ft_strcmp(arg + len - 4, ".cub") != 0)
	{
		error("the file is not final `.cub`!!");
		return (-1);
	}
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		error("the arg is a folder!!");
		close(fd);
		return (-1);
	}
	fd = open(arg, O_RDWR, 666);
	if (fd < 0)
	{
		error("the file is not exist!!");
		return (-1);
	}
	return (fd);
}

char	**get_full_file(int fd, char *arg, t_var *vars)
{
	char	*file;
	int		i;
	char	**file2d;

	(1) && (i = 0, file = get_next_line(fd));
	if (!file)
	{
		error("the file is empty!!");
		return (close(fd), NULL);
	}
	while (file)
		(1) && (free(file), i++, file = get_next_line(fd));
	file2d = (char **)malloc(sizeof(char *) * (i + 1));
	if (!file2d)
		return (close(fd), NULL);
	(1) && (close(fd), fd = open(arg, O_RDONLY), i = 0);
	if (fd < 0)
		return (free(file2d), NULL);
	file = get_next_line(fd);
	while (file)
		(1) && (file2d[i++] = file, file = get_next_line(fd));
	file2d[i] = NULL;
	return (close(fd), vars->len_lines = i, file2d);
}

int	checks(int fd, t_var *vars, char *av)
{
	vars->read_file = get_full_file(fd, av, vars);
	if (!vars->read_file)
		return (free(vars), 0);
	if (!check_configuration(vars->read_file, vars))
	{
		free_texture(vars);
		free2d(vars->read_file);
		free(vars);
		return (0);
	}
	if (!find_valid_map(vars))
	{
		free2d(vars->read_file);
		free_texture(vars);
		free(vars);
		return (0);
	}
	return (1);
}

t_var	*parcing(int ac, char **av)
{
	t_var	*vars;
	int		fd;

	if (ac != 2)
	{
		error("** Uncomplite Argument **");
		exit(1);
	}
	fd = check_file(av[1]);
	if (fd < 0)
		exit(1);
	vars = malloc(sizeof(t_var));
	if (!vars)
		return (NULL);
	if (checks(fd, vars, av[1]) == 0)
		return (NULL);
	return (vars);
}
