/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:07:45 by bchafi            #+#    #+#             */
/*   Updated: 2026/01/05 17:16:08 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parcing.h"

t_var	*initial_state(t_var *vars)
{
	vars->count_rgb = 0;
	vars->north = NULL;
	vars->south = NULL;
	vars->west = NULL;
	vars->east = NULL;
	vars->direction = 'S';
	vars->map = NULL;
	vars->map_s = NULL;
	vars->map_index = find_map_start(vars->read_file);
	if (vars->map_index < 0)
		return (error("No valid map found &!"), NULL);
	return (vars);
}

void	error(char *str)
{
	write(2, "## Error: ", 10);
	write(2, str, ft_strlen(str));
	write(2, "##\n", 3);
}

void	free2d(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_texture(t_var *vars)
{
	if (vars->north)
	{
		free(vars->north);
		vars->north = NULL;
	}
	if (vars->south)
	{
		free(vars->south);
		vars->south = NULL;
	}
	if (vars->west)
	{
		free(vars->west);
		vars->west = NULL;
	}
	if (vars->east)
	{
		free(vars->east);
		vars->east = NULL;
	}
}

int	is_seeing(char **file_line, char *side, int end, int n)
{
	int		i;
	char	*trimed;

	i = -1;
	while (file_line[++i] && i < end)
	{
		trimed = ft_strtrim(file_line[i], " \n\t");
		if (!ft_strncmp(trimed, side, n))
			return (free(trimed), 1);
		free(trimed);
	}
	return (0);
}
