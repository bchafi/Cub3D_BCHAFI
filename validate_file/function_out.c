/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:07:45 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/19 10:50:34 by bchafi           ###   ########.fr       */
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
	vars->map_index = find_map_start(vars->read_file);
    if (vars->map_index < 0)
        return (Error("No valid map found &!"), NULL);;
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

    if (!vars || !vars->map)
        return;
    i = 0;
	// ft_printf("Line_file: %d, line_map: %d\n", vars->len_lines, vars->map_index);
    // ft_printf("                        -------/* Configuration */------\n");
    // ft_printf("vars->NO : %s\n", vars->NO ? vars->NO : "(null)");
    // ft_printf("vars->SO : %s\n", vars->SO ? vars->SO : "(null)");
    // ft_printf("vars->WE : %s\n", vars->WE ? vars->WE : "(null)");
    // ft_printf("vars->EA : %s\n", vars->EA ? vars->EA : "(null)");
    // ft_printf("vars->floor_color : %d\n", vars->floor_color);
    // ft_printf("vars->earth_color : %d\n", vars->earth_color);
    // ft_printf(GRN UGRN BHGRN);
	// ft_printf("<<<<<<< Everythhing IS Done >>>>>>\n");
    // ft_printf(reset);
	// write(1, "******* Map *******\n", 21);
    while (vars->map[i] != NULL)
    {
        write(1, vars->map[i], ft_strlen(vars->map[i]));
		write(1, "\n", 1);
        i++;
    }
	if (!vars->map_s)
		return;
	i = 0;
	while (vars->map_s[i] != NULL)
    {
        write(1, vars->map_s[i], ft_strlen(vars->map_s[i]));
		write(1, "\n", 1);
        i++;
    }
}
