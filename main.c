/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@stu	dent.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 10:48:59 by yrhandou          #+#    #+#             */
/*   Updated: 2025/09/07 10:13:09 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void f(){system("leaks -quiet cub3D");}

// char **get_map1(t_var *vars, char **file, int start)
// {
//     vars->map = &file[start];
//     return (vars->map);
// }



int main(int ac, char **av)
{
	atexit(f);
	t_var vars;

	if (ac != 2)
	{
		Error("** Uncomplite Argument **");
		return (1);
	}
	int fd = check_file(av[1]);
	vars.read_file = get_full_file(fd, av[1], &vars);
	if (!vars.read_file)
		return (1);
	if(!check_configuration(vars.read_file, &vars))
		return (free2D(vars.read_file), 1);
	if (!find_valid_map(&vars))
		return (free2D(vars.read_file), free_textures(&vars), 1);
	/* Deployment */
	// Valid(&vars);
	/* cleanup */
    free2D(vars.read_file); // get_full_file
    free_textures(&vars); // check_configuration
    free2D(vars.map); // find_valid_map
    free2D(vars.map_s); //find_valid_map
	return (0);
}
