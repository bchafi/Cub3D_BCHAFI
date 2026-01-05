
#include "../cub3d.h"

void	alpha(t_unit *data, int column_id)
{
	float	strt_angle;
	float	ray_vec_x;
	float	ray_vec_y;

	strt_angle = (*data).angle + (VIEW_ANGLE / 2.0);
	while (strt_angle >= (*data).angle - (VIEW_ANGLE / 2.0) && column_id < WIDTH)
	{
		ray_vec_x = cos(strt_angle);
		ray_vec_y = sin(strt_angle);
		
		find_horizontal_intersection(data, ray_vec_x, ray_vec_y, strt_angle, column_id);
		find_vertical_intersection(data, ray_vec_x, ray_vec_y, strt_angle, column_id);
	
		strt_angle -= ANG_BETWEEN_RAYS;
		column_id++;
	}
	Draw_Walls(data);
}

void find_horizontal_intersection(t_unit *data, float ray_vec_x, float ray_vec_y, float angle, int column_id)
{
    float x_h, y_h;
    float x_i, y_i;

    if (ray_vec_y == 0)
        return (set_ray(data, HORIZONTAL, (float[]){-1, -1, -1}, column_id),(void)0);
    intial_horiz(data, ray_vec_x, ray_vec_y, (float*[]){&x_h, &y_h, &angle});
    if (ray_vec_y < 0)
        y_i = -CUBE_DIM;
    else
        y_i = CUBE_DIM;
    x_i = y_i * (ray_vec_x / ray_vec_y);

    while (1)
    {
        if (x_h < 0 || y_h < 0)
            return (set_ray(data, HORIZONTAL, (float[]){-1, -1, -1}, column_id), (void)0); 
        int check_y = (int)y_h;
        if (ray_vec_y < 0)
            check_y = (int)y_h - 1;
        float bias_x = (ray_vec_x > 0) ? 0.0001 : -0.0001;
        if (check_ifwall(data, (int)(x_h + bias_x), check_y) == YES)
            return (set_ray(data, HORIZONTAL, (float[]){x_h, y_h, angle}, column_id), (void)0);
        x_h += x_i;
        y_h += y_i;
    }
}

int intial_horiz(t_unit *data, float ray_vec_x, float ray_vec_y, float *coordi[3])
{
    float x_h, y_h;
    float dx, dy;

	if (ray_vec_y < 0)
		y_h = ((int)(data->player_posy / CUBE_DIM) * CUBE_DIM);
	else
		y_h = ((int)(data->player_posy / CUBE_DIM) * CUBE_DIM) + CUBE_DIM;

    dy = y_h - (*data).player_posy;
    
    dx = dy * (ray_vec_x / ray_vec_y);
    x_h = (*data).player_posx + dx;
    *coordi[0] = x_h;
    *coordi[1] = y_h;
    return YES;
}

void find_vertical_intersection(t_unit *data, float ray_vec_x, float ray_vec_y, float angle, int column_id)
{
    float x_v, y_v;
    float x_i, y_i;

    if (ray_vec_x == 0)
        return (set_ray(data, VERTICAL, (float[]){-1, -1, -1}, column_id),(void)0);
    intial_vert(data, ray_vec_x, ray_vec_y, (float*[]){&x_v, &y_v, &angle});
    if (ray_vec_x < 0)
        x_i = -CUBE_DIM;
    else
        x_i = CUBE_DIM;
    y_i = x_i * (ray_vec_y / ray_vec_x);
    while (1)
    {
        if (x_v < 0 || y_v < 0)
            return (set_ray(data, VERTICAL, (float[]){-1, -1, -1}, column_id),(void)0);
        int check_x = (int)x_v;
        if (ray_vec_x < 0)
            check_x = (int)x_v - 1; 
        float bias_y = (ray_vec_y > 0) ? 0.0001 : -0.0001;
        if (check_ifwall(data, check_x, (int)(y_v + bias_y)) == YES)
            return (set_ray(data, VERTICAL, (float[]){x_v, y_v, angle}, column_id), (void)0);
        x_v += x_i;
        y_v += y_i;
    }
}

int intial_vert(t_unit *data, float ray_vec_x, float ray_vec_y, float *coordi[3])
{
    float x_v, y_v;
    float dx, dy;

	if (ray_vec_x < 0)
		x_v = ((int)(data->player_posx / CUBE_DIM) * CUBE_DIM); 
	else
		x_v = ((int)(data->player_posx / CUBE_DIM) * CUBE_DIM) + CUBE_DIM;
    dx = x_v - (*data).player_posx;

    dy = dx * (ray_vec_y / ray_vec_x);
    y_v = (*data).player_posy + dy;

    *coordi[0] = x_v;
    *coordi[1] = y_v;
    return YES;
}
