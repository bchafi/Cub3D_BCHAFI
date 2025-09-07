/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:06:14 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/07 12:09:18 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char **parsing_map(int fd, char **arg)
{
    (void)arg;
    char *line;
    char **out;
    int i = 0;
    
    out = NULL;
    while ((line = get_next_line(fd)) != NULL)
    {
        out[i++] = line;
        free(line);
    }
    out[i] = 0;
    return (out);
}
