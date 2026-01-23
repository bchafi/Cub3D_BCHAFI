#include "../parcing.h"

static void in_player(t_unit *data, t_var *vars)
{
    data->pos_x = vars->x + 0.5;
    data->pos_y = vars->y + 0.5;
    data->move_speed = 0.1;
    data->rot_speed = 0.05;
    data->v_angle = FOV * PI / 180.0;
    data->angle_b_ray = data->v_angle / WIDTH;
    data->proj_plane_dist = ((WIDTH / 2.0)
            / tan(data->v_angle / 2.0));
    data->map = vars->map;
}

void init_player(t_unit *data, t_var *vars)
{
    data->map_width = vars->len_width;
    data->map_height = vars->lines_map;
    in_player(data, vars);
    if (vars->direction == 'N')
    {
        data->dir_x = 0;
        data->dir_y = -1;
        data->plane_x = data->v_angle;
        data->plane_y = 0;
    }
    else if (vars->direction == 'S')
    {
        data->dir_x = 0;
        data->dir_y = 1;
        data->plane_x = -data->v_angle;
        data->plane_y = 0;
    }
    else if (vars->direction == 'E')
    {
        data->dir_x = 1;
        data->dir_y = 0;
        data->plane_x = 0;
        data->plane_y = data->v_angle;
    }
    else if (vars->direction == 'W')
    {
        data->dir_x = -1;
        data->dir_y = 0;
        data->plane_x = 0;
        data->plane_y = -data->v_angle;
    }
}
int init_mlx(t_unit *core)
{
    core->mlx = mlx_init();
    if (!core->mlx)
        return (1);
    core->win = mlx_new_window(core->mlx, WIDTH, HEIGHT, "Bader_CUB3D");
    if (!core->win)
        return (free(core->mlx), 1);
    core->screen.img = mlx_new_image(core->mlx, WIDTH, HEIGHT);
    if (!core->screen.img)
    {
        mlx_destroy_window(core->mlx, core->win);
        return (free(core->mlx), 1);
    }
    core->screen.addr = mlx_get_data_addr(core->screen.img,
            &core->screen.bits_per_pixel, 
            &core->screen.line_length, 
            &core->screen.endian);
    if (!core->screen.addr)
    {
        mlx_destroy_window(core->mlx, core->win);
        mlx_destroy_image(core->mlx, core->screen.img);
        return (free(core->mlx), 1);
    }
    return (0);
}
