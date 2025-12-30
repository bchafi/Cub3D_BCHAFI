/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 07:57:17 by bkali             #+#    #+#             */
/*   Updated: 2025/12/29 04:31:17 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"


t_var parcing(int ac, char **av)
{
	t_var vars;
	int fd;

	if (ac != 2)
	{
		Error("** Uncomplite Argument **");
		exit(1);
	}
	fd = check_file(av[1]);
	vars.read_file = get_full_file(fd, av[1], &vars);
	if (!vars.read_file)
		exit(1);
	if(!check_configuration(vars.read_file, &vars))
	{
		free2D(vars.read_file);
		exit(1);
	}
	if (!find_valid_map(&vars))
	{
		free2D(vars.read_file);
		free_texture(&vars);
		exit(1);
	}
	return (vars);
}
void f(void){system("leaks cub3D");}



int main(int ac, char **av)
{
	atexit(f);
    parcing(ac, av);

    return (0);
}