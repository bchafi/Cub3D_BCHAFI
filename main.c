/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 07:57:17 by bkali             #+#    #+#             */
/*   Updated: 2026/01/05 17:30:20 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"
#include "./cub3d.h"

void	ft_free_alls(t_var *vars)
{
	if (vars->map)
		free2d(vars->map);
	if (vars->map_s)
		free2d(vars->map_s);
	free_texture(vars);
	if (vars->read_file)
		free2d(vars->read_file);
	free(vars);
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

int	main(int ac, char **av)
{
	t_var	*vars;

	vars = parcing(ac, av);
	if (!vars)
		return (1);
	ray_casting_entry(vars, vars->map);
	ft_free_alls(vars);
	return (0);
}
