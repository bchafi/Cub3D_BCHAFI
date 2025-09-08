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

int main(int ac, char **av)
{
	// t_cube cub;
	t_var *vars;
	if (ac != 2)
	{
		write(2, "** Uncomplite Argument **\n", 27);
		exit(1000);
	}
	int fd = check_file(av[1]);
	char **file2D = get_map(fd, av[1], vars);
	return (0);
}
