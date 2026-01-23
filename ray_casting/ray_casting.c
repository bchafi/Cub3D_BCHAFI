#include "../parcing.h"

void my_mlx_pixel_put(t_unit *data, int x, int y, int color)
{
    char *dst;
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = data->screen.addr + (y * data->screen.line_length + x * (data->screen.bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void load_one_texture(t_unit *p, int i, char *path)
{
    p->tex[i].img = mlx_xpm_file_to_image(p->mlx, path,
                                          &p->tex[i].width, &p->tex[i].height);

    if (!p->tex[i].img)
    {
        printf("Error\nCannot load texture: %s\n", path);
        exit(1);
    }
    p->tex[i].addr = mlx_get_data_addr(p->tex[i].img,
                                       &p->tex[i].bits_per_pixel, &p->tex[i].line_length, &p->tex[i].endian);
}

void init_textures(t_unit *p, t_var *vars)
{
    load_one_texture(p, 0, vars->north);
    load_one_texture(p, 1, vars->south);
    load_one_texture(p, 2, vars->west);
    load_one_texture(p, 3, vars->east);
}

int get_texture_color(t_img *tex, int x, int y)
{
    char *dst;
    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return (0);
    dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
    return (*(unsigned int *)dst);
}

int main_work(t_unit *p)
{
    move_player(p);
    // This function will handle the main rendering loop
    // Clear the image buffer
    // Perform raycasting calculations
    // Draw the scene based on raycasting results
    // Update the window with the new image
    // For now, we will just print a message

    int x = 0;
    // ... (Define all your variables here as before) ...
    double cameraX, rayDirX, rayDirY;
    int mapX, mapY, stepX, stepY, hit, side;
    double sideDistX, sideDistY, deltaDistX, deltaDistY, perpWallDist;
    int lineHeight, drawStart, drawEnd;

    // Texture variables
    double wallX;
    int texX, texY;
    double step, texPos;
    int texIndex;

    while (x < WIDTH)
    {
        // 1. Ray Calculation (Same as before)
        cameraX = 2 * x / (double)WIDTH - 1;
        rayDirX = p->dir_x + p->plane_x * cameraX;
        rayDirY = p->dir_y + p->plane_y * cameraX;

        mapX = (int)p->pos_x;
        mapY = (int)p->pos_y;

        deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        // 2. Step Calculation (Same as before)
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (p->pos_x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - p->pos_x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (p->pos_y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - p->pos_y) * deltaDistY;
        }

        hit = 0;
        while (hit == 0)
        {
            // ... (Your existing step logic: sideDist vs sideDist) ...
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            // --- 🔴 ADD THIS SAFETY CHECK ---
            if (mapX < 0 || mapX >= p->map_width || mapY < 0 || mapY >= p->map_height)
            {
                hit = 1; // Stop the ray
                break;   // Exit the loop immediately to avoid crash
            }
            // -------------------------------

            // Now it is safe to check the map
            if (p->map[mapY][mapX] == '1')
                hit = 1;
        }

        // 4. Wall Distance & Height
        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);

        lineHeight = (int)(HEIGHT / perpWallDist);
        drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT)
            drawEnd = HEIGHT - 1;

        // --- TEXTURE CALCULATION STARTS HERE ---

        // 5. Determine which texture to use
        if (side == 0)                        // East/West
            texIndex = (rayDirX > 0) ? 3 : 2; // 3=East, 2=West
        else                                  // North/South
            texIndex = (rayDirY > 0) ? 1 : 0; // 1=South, 0=North

        // 6. Calculate exactly where the wall was hit (0.0 to 1.0)
        if (side == 0)
            wallX = p->pos_y + perpWallDist * rayDirY;
        else
            wallX = p->pos_x + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        // 7. Calculate X coordinate on the texture
        texX = (int)(wallX * (double)p->tex[texIndex].width);
        if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
            texX = p->tex[texIndex].width - texX - 1;

        // 8. Prepare Y coordinate stepping
        step = 1.0 * p->tex[texIndex].height / lineHeight;
        texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

        // 9. DRAW THE PIXELS
        // Ceiling
        for (int y = 0; y < drawStart; y++)
            my_mlx_pixel_put(p, x, y, 0x000000); // Ceiling color

        // Wall
        for (int y = drawStart; y < drawEnd; y++)
        {
            texY = (int)texPos & (p->tex[texIndex].height - 1);
            texPos += step;
            int color = get_texture_color(&p->tex[texIndex], texX, texY);
            my_mlx_pixel_put(p, x, y, color);
        }

        // Floor
        for (int y = drawEnd; y < HEIGHT; y++)
            my_mlx_pixel_put(p, x, y, 0x444444); // Floor color

        x++;
    }
    mlx_put_image_to_window(p->mlx, p->win, p->screen.img, 0, 0);
    return (0);
}

void raycast_engine(t_var *vars)
{
    t_unit player;

    init_player(&player, vars);
    if (init_mlx(&player))
    {
        ft_free_alls(vars, NULL);
        printf("Error initializing MLX\n");
        return;
    }
    init_textures(&player, vars);
    printf("Raycasting engine initialized successfully!\n");
    mlx_hook(player.win, 2, 1L, key_press, &player);
    mlx_hook(player.win, 3, 2L, key_release, &player);
    mlx_hook(player.win, 17, 0, close_window, &player);
    mlx_loop_hook(player.mlx, main_work, &player);
    move_player(&player);
    mlx_loop(player.mlx);
    ft_free_alls(vars, &player);
}