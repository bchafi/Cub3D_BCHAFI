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

#include "../parcing.h"


int first_march(int ac, char **av)
{
	t_var vars;
	/* Deployment */
	// Valid(&vars);
	/* cleanup */
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
		return (free2D(vars.read_file), free_texture(&vars), 1);
	return (0);
}
