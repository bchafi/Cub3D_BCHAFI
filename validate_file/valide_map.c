/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:21:01 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/20 09:54:57 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int is_valid_char(char c)
{
    return (c == '0' || c == '1' ||
            c == 'N' || c == 'S' || c == 'E' || c == 'W' ||
            c == ' ');
}

int validate_map(t_var *vars)
{
    int i, j;
    int player_count = 0;

    i = 2;
    while (vars->map_s[i + 1])
    {
        j = 1;
        while (vars->map_s[i][j])
        {
            char c = vars->map_s[i][j];

            if (!is_valid_char(c))
                return (Error("Invalid character in map"), 0);

            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                player_count++;

            if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                if (vars->map_s[i-1][j] == ' ' || vars->map_s[i+1][j] == ' ' ||
                    vars->map_s[i][j-1] == ' ' || vars->map_s[i][j+1] == ' ')
                {
                    return (Error("Map not surrounded by walls"), 0);
                }
            }
            j++;
        }
        i++;
    }
    if (player_count != 1)
        return (Error("Map must contain exactly one player spawn"), 0);

    return (1);
}