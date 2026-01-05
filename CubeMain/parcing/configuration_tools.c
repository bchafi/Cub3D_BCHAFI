/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configuration_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 10:07:45 by bchafi            #+#    #+#             */
/*   Updated: 2026/01/04 19:17:15 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parcing.h"

int type_file_line(t_var *vars, char **file_line, char *trimed, int i, int *len)
{
    if (is_line_map(trimed))
    {
        if (*len != 6)
            return (Error("Missing texture/color configuration 2!"), 0);
        return ((*len)++, vars->map_index = i, 2);
    }
    else if (!ft_strncmp("NO ", trimed, 3)
            || !ft_strncmp("SO ", trimed, 3)
            || !ft_strncmp("WE ", trimed, 3)
            || !ft_strncmp("EA ", trimed, 3))
    {
        if (!handle_texture_line(vars, file_line, trimed, i))
            return (0);
        (*len)++;
    }
    else if (!ft_strncmp("F ", trimed, 2) ||
             !ft_strncmp("C ", trimed, 2))
    {
        if (!handle_color_line(vars, file_line, trimed, i))
            return (0);
        (*len)++;
    }
    else if (ft_isalpha(trimed[0]))
        return (Error("Line Configuration Wrong!"), 0);
    return (1);
}

int check_file_lines(char **file_line, t_var *vars, int *len)
{
    int     i;
    char    *trimed;
    int     status;

    i = -1;
    while (file_line[++i] != NULL)
    {
        trimed = ft_strtrim(file_line[i], " \n\t");
        if (!trimed || !*trimed)
        {
            free(trimed);
            continue;
        }
        status = type_file_line(vars, file_line, trimed, i, len);
        free(trimed);
        if (status == 0)
            return (0);
        if (status == 2)
            return (2);
    }
    return (1);
}

int is_line_map(char *file_line)
{
    int i = 0;

    while (file_line[i])
    {
        if (file_line[i] != '0' && file_line[i] != '1'
            && file_line[i] != ' ' && file_line[i] != '\t')
            return (0);
        i++;
    }
    return (1);
}

int handle_texture_line(t_var *vars, char **file_line, char *trimed, int i)
{
    if (is_seeing(file_line, trimed, i, 3) || file_line[i][0] == ' ')
    {
        Error("Duplicate texture/color configuration | ' '!");
        return (0);
    }
    if (!check_tex(vars, trimed))
        return (0);
    return (1);
}

int handle_color_line(t_var *vars, char **file_line, char *trimed, int i)
{
    if (is_seeing(file_line, trimed, i, 2) || file_line[i][0] == ' ')
    {
        Error("Wrong texture/color configuration!!");
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
