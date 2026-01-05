/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:21:01 by bchafi            #+#    #+#             */
/*   Updated: 2026/01/04 22:21:15 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parcing.h"

int is_valid_char(char c)
{
    return (c == '0' || c == '1' ||
            c == 'N' || c == 'S' || c == 'E' || c == 'W' ||
            c == ' ');
}

int check_validaion_maps(t_var *vars, int i, int j, char c)
{
    int     count;

    count = 0;
    if (!is_valid_char(c))
        return (Error("Invalid character in map"), -1);
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        count++;
        vars->direction = c;
        vars->x = j;
        vars->y = i;
    }
    if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        if (vars->map_s[i - 1][j] == ' ' || 
            vars->map_s[i + 1][j] == ' ' ||
            vars->map_s[i][j - 1] == ' ' || 
            vars->map_s[i][j + 1] == ' ')
        {
            return (Error("Map not surrounded by walls"), -1);
        }
    }
    return (count);
}

int validate_map(t_var *vars)
{
    int i;
    int j;
    int player_count;

    player_count = 0;
    i = 1; 
    while (vars->map_s[i + 1])
    {
        j = 1;
        while (vars->map_s[i][j])
        {
            char c = vars->map_s[i][j];
            
            if (check_validaion_maps(vars, i, j, c) == -1)
                return (0);
            player_count += check_validaion_maps(vars, i, j, c);
            j++;
        }
        i++;
    }
    if (player_count != 1)
        return (Error("Map must contain exactly one player"), 0);

    return (1);
}