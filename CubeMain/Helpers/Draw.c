
#include "../cub3d.h"


void	Draw_Walls(t_unit *data)
{
	t_ray	*ray;
	float	height;
	static int flag;

	ray = (*data).ray;
	dprintf((*data).fd, "\n\nRound: %d", flag);
	flag++;
	while (ray)
	{
		height = (CUBE_DIM * 2.5 / (*(*ray).nearest).distance) * PROJ_PLANE_DIST;
		draw_straps(data, (*ray).id, (int)height, (*ray).nearest);
		ray = (*ray).next;
	}
	mlx_put_image_to_window((*data).mlx, (*data).mlx_window, (*data).img, 0, 0);
}

void	fix_mirroring(float *partition, t_texture **Var, t_unit *data, t_intersection *intersection)
{
    if (!intersection->is_vertical)
    {
        if (sin(intersection->angle) < 0) 
            *Var = &(data->texture[0]);
        else 
        {
            *Var = &(data->texture[1]);
            *partition = 1.0 - *partition; 
        }
    }
    else
    {
        if (cos(intersection->angle) > 0)
        {
            *Var = &(data->texture[3]);
        }
        else 
        {
            *Var = &(data->texture[2]);
            *partition = 1.0 - *partition; 
        }
    }
}

void	draw_straps(t_unit *data, int column, float height, t_intersection *nearest)
{
	float partition;
	float step;
	float tex_pos;
	int y;
	t_texture *texture;

	partition = nearest->x;
	if (nearest->is_vertical)
		partition = nearest->y;
	partition = partition / CUBE_DIM;
	partition -= floor(partition); 
    if (partition >= 1.0) partition = 0.9999;
    if (partition < 0) partition = 0;

	fix_mirroring(&partition, &texture, data, nearest);
	int tex_x = (int)((*texture).width * partition);
    int draw_start = (HEIGHT - height) / 2;
    int draw_end = (HEIGHT + height) / 2;

    if (draw_start < 0) 
        draw_start = 0;
    if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;
	y = 0;
    while (y < draw_start)
    {
        safe_pixel_write(data, column, y, data->celling_color);
        y++;
    }
    step = 1.0 * (*texture).height / height;
    tex_pos = (draw_start - (HEIGHT - height) / 2) * step;
    y = draw_start;
	while (y < draw_end)
	{
		int tex_y = (int)tex_pos; 
		if (tex_y >= (*texture).height)
		tex_y = (*texture).height - 1;
		tex_pos += step; 
		
		char *pixel_addr;
		int  offset;
		if (tex_x >= (*texture).width)
			tex_x = (*texture).width - 1;
			
		offset = (tex_y * (*texture).line_lenght) + (tex_x * ((*texture).bpp / 8));
		pixel_addr = (*texture).addr + offset;
		unsigned int color = *(unsigned int *)pixel_addr;
		
		safe_pixel_write(data, column, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		safe_pixel_write(data, column, y, data->floor_color);
		y++;
	}
}

void	draw_column(t_unit *data, int height, int column, t_intersection *nearest)
{
	
	draw_straps(data, column, height, nearest);
}

void	create_ray(t_unit *data, t_intersection *vertical, t_intersection *horizontal, int id)
{
	t_ray	*head;
	t_ray	*hold;

	if (!(*data).ray)
	{
		(*data).ray = ft_malloc(sizeof(t_ray));
		head = (*data).ray;
		(*head).next = NULL;
		(*head).id = id; 
		(*head).horizontal = horizontal;
		(*head).horizontal->is_vertical = 0;
		(*head).vertical = vertical;
		(*head).vertical->is_vertical = 1;
		(*head).nearest = smallest((*head).vertical, (*head).horizontal);
		return;
	}
	head = (*data).ray;
	while (head)
	{
		hold = head;
		head = (*head).next;
	}
	(*hold).next = ft_malloc(sizeof(t_ray));
	head = (*hold).next;
	(*head).id = id;
	(*head).next = NULL;
	(*head).horizontal = horizontal;
	(*head).horizontal->is_vertical = 0;
	(*head).vertical = vertical;
	(*head).vertical->is_vertical = 1;
	(*head).nearest = smallest((*head).vertical, (*head).horizontal);
}

t_intersection	*smallest(t_intersection *vertical, t_intersection *horizontal)
{
	if ((*vertical).distance > (*horizontal).distance)
		return (horizontal);
	else
		return (vertical);
}
