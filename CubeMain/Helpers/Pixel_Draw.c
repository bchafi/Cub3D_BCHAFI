#include "../cub3d.h"

void	write_pixel(t_unit *data, int x, int y, int color)
{
	char	*dst;

	dst = (*data).addr + (y * (*data).line_length + x * ((*data).bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	safe_pixel_write(t_unit *data, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	write_pixel(data, x, y, color);
}

//void draw_line(t_unit *data, float x0f, float y0f, float x1f, float y1f, int color)
//{
//    int x0 = (int)(x0f + 0.5f);
//    int y0 = (int)(y0f + 0.5f);
//    int x1 = (int)(x1f + 0.5f);
//    int y1 = (int)(y1f + 0.5f);

//    int dx = abs(x1 - x0);
//    int dy = -abs(y1 - y0);
//    int sx = (x0 < x1) ? 1 : -1;
//    int sy = (y0 < y1) ? 1 : -1;
//    int err = dx + dy;

//    while (1)
//    {
//        safe_pixel_write(data, x0, y0, color);
//        if (x0 == x1 && y0 == y1)
//            break;
//        int e2 = 2 * err;
//        if (e2 >= dy)
//        {
//            err += dy;
//            x0 += sx;
//        }
//        if (e2 <= dx)
//        {
//            err += dx;
//            y0 += sy;
//        }
//    }
//}
//void	draw_player(t_unit *data, int pos_x, int pos_y)
//{
//	int	x;
//	int	y;
//	//int	a;

//	//a = 0;
//	x = 0;
//	y = 0;
//	if (pos_x < 0 || pos_x > WIDTH || pos_y < 0 || pos_y > HEIGHT)
//		write(2, "\nInvalid Player Position !", 27), exit(1);
//	draw_line(data, (*data).player_posx, (*data).player_posy, (*data).ray_tip_x, ((*data).ray_tip_y), RAY_COLOR);
//	x = pos_x - 10;
//	y = pos_y - 10;
//	while (y < pos_y + 10)
//	{
//		x = pos_x - 10;
//		while (x < pos_x + 10)
//		{
//			safe_pixel_write(data, x, y, 0xFF0000);
//			x++;
//		}
//		y++;
//	}
//	mlx_put_image_to_window((*data).mlx, (*data).mlx_window, (*data).img, 0, 0);
////}

//void	player_pos_clean(t_unit *data, int pos_x, int pos_y, int backgrnd_color)
//{
//	int	x;
//	int	y;

//	x = pos_x - 10;
//	y = pos_y - 10;
//	while (y < pos_y+ 10)
//	{
//		x = pos_x - 10;
//		while (x < pos_x + 10)
//		{
//			safe_pixel_write(data, x, y, backgrnd_color);
//			x++;
//		}
//		y++;
//	}
//	x = pos_x - 3;
//	y = pos_y - 60;
//	while (y < pos_y)
//	{
//		x = pos_x - 3;
//		while (x <  pos_x + 3)
//		{
//			safe_pixel_write(data, x, y, backgrnd_color);
//			x++;
//		}
//		y++;
//	}
//	mlx_put_image_to_window((*data).mlx, (*data).mlx_window, (*data).img, 0, 0);
//	draw_line(data, (*data).player_posx, (*data).player_posy, (*data).ray_tip_x, (*data).ray_tip_y, BACKGROUND);

//}
