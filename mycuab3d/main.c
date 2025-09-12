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

int main(int ac, char **av)
{
	atexit(f);
	t_var vars;

	if (ac != 2)
	{
		write(2, "** Uncomplite Argument **\n", 27);
		return (1);
	}
	int fd = check_file(av[1]);
	vars.read_file = get_map(fd, av[1], &vars);
	if (!vars.read_file)
		return (1);
	if(!check_sides_tex(vars.read_file, &vars))
		return (free2D(vars.read_file), 1);
	
	
	return (free2D(vars.read_file), free_textures(&vars), 0);// 
}

	// if (!check_texturs(vars.read_file, vars))
	// 	return (free2D(vars.read_file), 1);
	// int i = 0;
	
	// while (*vars.read_file != NULL)
	// {
	// 	printf("%s", *vars.read_file);
	// 	vars.read_file++;
	// }
	// printf("NO : %s\n", vars.NO);
	// printf("SO : %s\n", vars.SO);
	// printf("WE : %s\n", vars.WE);
	// printf("EA : %s\n", vars.EA);
	// printf("F : %s\n", vars.F);
	// printf("C : %s\n", vars.C);