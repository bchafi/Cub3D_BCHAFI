/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 07:57:17 by bkali             #+#    #+#             */
/*   Updated: 2026/01/11 14:28:50 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"
#include "./cub3d.h"

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
