/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configuration_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:07:45 by bchafi            #+#    #+#             */
/*   Updated: 2026/01/05 17:14:45 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parcing.h"

int	type_file_line(t_var *vars, char **file_line, char *trimed, int i)
{
	if (is_line_map(trimed))
	{
		if (vars->len_cline != 6)
			return (error("Missing texture/color configuration 2!"), 0);
		return (vars->len_cline++, vars->map_index = i, 2);
	}
	else if (!ft_strncmp("NO ", trimed, 3)
		|| !ft_strncmp("SO ", trimed, 3)
		|| !ft_strncmp("WE ", trimed, 3) || !ft_strncmp("EA ", trimed, 3))
	{
		if (!handle_texture_line(vars, file_line, trimed, i))
			return (0);
		vars->len_cline++;
	}
	else if (!ft_strncmp("F ", trimed, 2)
		|| !ft_strncmp("C ", trimed, 2))
	{
		if (!handle_color_line(vars, file_line, trimed, i))
			return (0);
		vars->len_cline++;
	}
	else if (ft_isalpha(trimed[0]))
		return (error("Line Configuration Wrong!"), 0);
	return (1);
}

int	check_file_lines(char **file_line, t_var *vars)
{
	int		i;
	char	*trimed;
	int		status;

	i = -1;
	while (file_line[++i] != NULL)
	{
		trimed = ft_strtrim(file_line[i], " \n\t");
		if (!trimed || !*trimed)
		{
			free(trimed);
			continue ;
		}
		status = type_file_line(vars, file_line, trimed, i);
		free(trimed);
		if (status == 0)
			return (0);
		if (status == 2)
			return (2);
	}
	return (1);
}

int	is_line_map(char *file_line)
{
	int	i;

	i = 0;
	while (file_line[i])
	{
		if (file_line[i] != '0' && file_line[i] != '1'
			&& file_line[i] != ' ' && file_line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	handle_texture_line(t_var *vars, char **file_line, char *trimed, int i)
{
	if (is_seeing(file_line, trimed, i, 3) || file_line[i][0] == ' ')
	{
		error("Duplicate texture/color configuration | ' '!");
		return (0);
	}
	if (!check_tex(vars, trimed))
		return (0);
	return (1);
}

int	handle_color_line(t_var *vars, char **file_line, char *trimed, int i)
{
	if (is_seeing(file_line, trimed, i, 2) || file_line[i][0] == ' ')
	{
		error("Wrong texture/color configuration!!");
		return (0);
	}
	else if (!ft_strncmp("F ", trimed, 2))
	{
		if (!check_color(vars, trimed, 1))
			return (0);
	}
	else if (!ft_strncmp("C ", trimed, 2))
	{
		if (!check_color(vars, trimed, 0))
			return (0);
	}
	return (1);
}
