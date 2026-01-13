#include "../cub3d.h"

void init_player(t_unit *data, t_var *map)
{
    data->pos_x = map->x + 0.5;
    data->pos_y = map->y + 0.5;

    if (map->direction == 'N')
    {
        data->dir_x = 0;
        data->dir_y = -1;
        data->plane_x = 0.66;
        data->plane_y = 0;
    }
}

void    raycast_engine(t_var *vars)
{
    t_unit* player;

    init_player(player, vars);
    
}