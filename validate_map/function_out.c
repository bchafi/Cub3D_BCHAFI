/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:07:45 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/16 11:40:49 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_var *initial_state(t_var *vars)
{
	vars->count_rgb = 0;
	vars->NO = NULL;
	vars->SO = NULL;
	vars->WE = NULL;
	vars->EA = NULL;
	vars->map_index = -1;
	return (vars);
}

void free_textures(t_var *vars)
{
	free(vars->NO);
	vars->NO = NULL;
	free(vars->SO);
	vars->SO = NULL;
	free(vars->WE);
	vars->WE = NULL;
	free(vars->EA);
	vars->EA = NULL;
}




int is_seeing(char **file_line, char *side, int end, int n)
{
	int i;

	i = -1;
	while (file_line[++i] && i < end)
	{
		char *trimed = ft_strtrim(file_line[i], " \n\t");
		if (!ft_strncmp(trimed, side, n))
			return (free(trimed), 1);
		free(trimed);
	}
	return (0);
}

// Clean
void Valid(t_var *vars)
{
    int i;

    if (!vars || !vars->read_file)
        return;

    i = 0;
    while (vars->read_file[i] != NULL)
    {
        ft_printf("%s", vars->read_file[i]);
        i++;
    }
	
    ft_printf("-------/* Deployment */------\n");
    ft_printf("vars->NO : %s\n", vars->NO ? vars->NO : "(null)");
    ft_printf("vars->SO : %s\n", vars->SO ? vars->SO : "(null)");
    ft_printf("vars->WE : %s\n", vars->WE ? vars->WE : "(null)");
    ft_printf("vars->EA : %s\n", vars->EA ? vars->EA : "(null)");
    ft_printf("vars->floor_color : %d\n", vars->floor_color);
    ft_printf("vars->earth_color : %d\n", vars->earth_color);
    ft_printf(GRN UGRN BHGRN);
	ft_printf("<<<<<<< Everythhing IS Done >>>>>>\n");
    ft_printf(reset);
}
