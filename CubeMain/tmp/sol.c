//#include "../cub3d.h"

//// ADD THESE TO YOUR cub3d.h
//// #define TEXTURE_WIDTH 64
//// #define TEXTURE_HEIGHT 64

///*
//* You will need a helper function like this in one of your files.
//* It gets the color from your parsed XPM image data.
//* (This is just an example, yours might be different)
//*/
///*
//int get_pixel_color(t_texture *tex, int x, int y)
//{
//    char *dst;

//    if (x < 0 || x >= TEXTURE_WIDTH || y < 0 || y >= TEXTURE_HEIGHT)
//        return (0x0); // Return black if out of bounds
//    dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
//    return (*(unsigned int *)dst);
//}
//*/

///**
// * This function calculates the texture_x coordinate and
// * figures out *which* texture to use (NO, SO, WE, EA).
// */
//void Draw_Walls(t_unit *data)
//{
//	t_ray	*ray;
//	float	height;
//	int		tex_x; // The X-coordinate on the texture
//	t_texture *texture_to_use; // The texture (NO, SO, WE, EA)

//	ray = (*data).ray;
//	while (ray)
//	{
//		height = (CUBE_DIM / (*(*ray).nearest).distance) * PROJ_PLANE_DIST;
		
//		// --- 1. FIND THE WALL HIT FRACTION ---
//		double wall_hit_fraction;
//		if ((*ray).nearest == (*ray).vertical)
//		{
//			// Hit an East/West wall, so use the Y coordinate
//			wall_hit_fraction = (*(*ray).nearest).y - floor((*(*ray).nearest).y);
			
//			// --- 2. FIGURE OUT WHICH TEXTURE (EAST or WEST) ---
//			if (cos((*(*ray).nearest).angle) > 0) // Pointing right
//				texture_to_use = &data->map_s->ea_texture; // EAST
//			else
//				texture_to_use = &data->map_s->we_texture; // WEST
//		}
//		else // nearest == horizontal
//		{
//			// Hit a North/South wall, so use the X coordinate
//			wall_hit_fraction = (*(*ray).nearest).x - floor((*(*ray).nearest).x);

//			// --- 2. FIGURE OUT WHICH TEXTURE (NORTH or SOUTH) ---
//			if (sin((*(*ray).nearest).angle) > 0) // Pointing down
//				texture_to_use = &data->map_s->so_texture; // SOUTH
//			else
//				texture_to_use = &data->map_s->no_texture; // NORTH
//		}

//		// --- 3. CALCULATE TEXTURE_X ---
//		tex_x = (int)(wall_hit_fraction * (double)TEXTURE_WIDTH);

//		// --- 4. "FLIP" THE TEXTURE IF NEEDED ---
//		// If ray hits WEST wall, flip X
//		if ((*ray).nearest == (*ray).vertical && cos((*(*ray).nearest).angle) < 0)
//			tex_x = TEXTURE_WIDTH - 1 - tex_x;
//		// If ray hits NORTH wall, flip X
//		if ((*ray).nearest == (*ray).horizontal && sin((*(*ray).nearest).angle) > 0)
//			tex_x = TEXTURE_WIDTH - 1 - tex_x;

//		// --- 5. PASS THE INFO TO THE DRAW FUNCTION ---
//		draw_column(data, (int)height, (*ray).id, tex_x, texture_to_use);
		
//		ray = (*ray).next;
//	}
//	mlx_put_image_to_window((*data).mlx, (*data).mlx_window, (*data).img, 0, 0);
//}

///**
// * This function now takes the texture_x and the texture pointer
// * and draws the textured slice.
// */
//void draw_column(t_unit *data, int height, int column, int tex_x, t_texture *texture)
//{
//	int	y;
//	int y_top;
//	int y_bottom;
//	// float horizon_line = (HEIGHT / 2) + 200; // Unused

//	y_top = (HEIGHT / 2) - (height / 2);
//	y_bottom = (HEIGHT / 2) + (height / 2);

//	// Clamp the wall top and bottom to the screen bounds
//	int draw_start = y_top;
//	if (draw_start < 0)
//		draw_start = 0;
	
//	int draw_end = y_bottom;
//	if (draw_end >= HEIGHT)
//		draw_end = HEIGHT; // Use HEIGHT, not HEIGHT - 1, for the loop

//	y = 0;
//	while (y < HEIGHT)
//	{
//		// 1. Draw CEILING
//		if (y < draw_start)
//			write_pixel(data, column, y, data->map_s->final_c);
		
//		// 2. Draw WALL (The new textured part)
//		else if (y >= draw_start && y < draw_end)
//		{
//			// --- 6. CALCULATE TEXTURE_Y ---
//			// Calculate the Y coordinate on the texture
//			int tex_y = (int)(((double)(y - y_top) / (double)height) * (double)TEXTURE_HEIGHT);

//			// --- 7. GET THE COLOR FROM THE TEXTURE ---
//			// (I am assuming you have a get_pixel_color function)
//			int color = get_pixel_color(texture, tex_x, tex_y);
			
//			write_pixel(data, column, y, color);
//		}
//		// 3. Draw FLOOR
//		else // y >= draw_end
//			write_pixel(data, column, y, data->map_s->final_f);
//		y++;
//	}
//}

//// (Make sure to update the prototype for draw_column in cub3d.h)ii
//// ... rest of your file (create_ray, smallest) ...