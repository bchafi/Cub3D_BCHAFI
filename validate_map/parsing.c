/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:06:14 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/08 09:04:48 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


char **parsing_map(int fd)
{
    char *line;
    char **out = NULL;
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


// t_obj	*get_map(int fd, t_obj *g, char *fds)
// {
// 	char	*map;
// 	int		i;
// 	char	**s_map;

// 	(1) && (i = 0, map = get_next_line(fd));
// 	if (!map)
// 	{
// 		close(fd);
// 		ft_error("** the map is empty **");
// 	}
// 	while (map)
// 		(1) && (free(map), i++, map = get_next_line(fd));
// 	s_map = (char **)malloc(sizeof(char *) * (i + 1));
// 	if (!s_map)
// 		return (free(g), NULL);
// 	(1) && (close(fd), fd = open(fds, O_RDONLY), i = 0);
// 	if (fd < 0)
// 		return (free(s_map), free(g), NULL);
// 	map = get_next_line(fd);
// 	while (map)
// 		(1) && (s_map[i++] = map, map = get_next_line(fd));
// 	(1) && (s_map[i] = NULL, g->map = s_map, g->len_line = i);
// 	return (close(fd), g);
// }