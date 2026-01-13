/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 07:57:17 by bkali             #+#    #+#             */
/*   Updated: 2026/01/12 18:55:08 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parcing.h"

int	main(int ac, char **av)
{
	t_var	*vars;
	
	vars = parcing(ac, av);
	if (!vars)
		return (1);
	
	// raycast_engine && steps to render the 3D view would go here
	raycast_engine(vars);
	ft_free_alls(vars);
	return (0);
}
