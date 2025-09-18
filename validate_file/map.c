/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:21:01 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/18 10:23:59 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char *multi_space(int len)
{
    char *line = malloc(len + 1);
    if (!line)
        return (NULL);
    int i = -1;
    while (++i < (len + 2))
        line[i] = ' ';
    line[i] = '\0';
    return (line);
}

char **get_map(t_var *vars, char **file, int start)
{
    char **maping;
    int count;
    int i;
    int len;
    count = 0;
    i = start;
    while (file[i])
        (1) && (count++, i++);
    maping = malloc(sizeof(char *) * (count + 1));
    if (!maping)
        return (Error("Allocation Fail maping!!"), NULL);
    i = 0;
    ft_printf("i: %d, map: %s\n", vars->map_index, file[start]);
    while (file[start] && start < vars->len_lines)
    {
        maping[i] = ft_strtrim(file[start], "\n");
        len = ft_strlen(maping[i]);
        if (vars->len_width < len)
            vars->len_width = len;
        (1) && (start++, i++);
    }
    maping[i] = NULL;
    return (vars->map = maping, vars->lines_map = count, maping);
}
// char **map_copy_s(t_var *var, char **map)
// {
//     int i = 0;
//     int j;
//     int size = var->lines_map + 2; // +2 for top and bottom borders
//     char **squer_map = malloc(sizeof(char *) * (size + 1));
//     if (!squer_map)
//         return (NULL);

//     // Top border
//     squer_map[0] = multi_space(var->len_width + 2);

//     // Copy map rows, padding with spaces
//     while (map[i])
//     {
//         int len = ft_strlen(map[i]);
//         squer_map[i + 1] = malloc(var->len_width + 3); // +2 for borders +1 for \0
//         if (!squer_map[i + 1])
//             return (free2D(squer_map), NULL);

//         squer_map[i + 1][0] = ' '; // left border
//         for (j = 0; j < var->len_width; j++)
//         {
//             if (j < len)
//                 squer_map[i + 1][j + 1] = map[i][j];
//             else
//                 squer_map[i + 1][j + 1] = ' '; // pad with space
//         }
//         squer_map[i + 1][j + 1] = ' '; // right border
//         squer_map[i + 1][j + 2] = '\0';
//         i++;
//     }

//     // Bottom border
//     squer_map[i + 1] = multi_space(var->len_width + 2);
//     squer_map[i + 2] = NULL;

//     return squer_map;
// }

char **check_map(t_var *vars)
{
    vars->map = get_map(vars, vars->read_file, vars->map_index);
    if (!vars->map)
        return (NULL);

    // vars->map_s = map_copy_s(vars, vars->map);
    // if (!vars->map_s)
    //     return (free2D(vars->map), NULL);
        
    return (vars->map);
}
