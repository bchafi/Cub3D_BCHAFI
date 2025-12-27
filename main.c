/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 07:57:17 by bkali             #+#    #+#             */
/*   Updated: 2025/12/27 14:35:51 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parcing.h"

void key_hook(mlx_key_data_t keydata, void *param)
{
    mlx_t *mlx = (mlx_t *)param;
    
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_printf(UGRN "Press ESC Key !!\n" reset);
        mlx_close_window(mlx);
	}
}

t_var parcing(int ac, char **av)
{
	t_var vars;
	int fd;

	if (ac != 2)
	{
		Error("** Uncomplite Argument **");
		exit(1);
	}
	fd = check_file(av[1]);
	vars.read_file = get_full_file(fd, av[1], &vars);
	if (!vars.read_file)
		exit(1);
	if(!check_configuration(vars.read_file, &vars))
	{
		free2D(vars.read_file);
		exit(1);
	}
	if (!find_valid_map(&vars))
	{
		free2D(vars.read_file);
		free_textures(&vars);
		exit(1);
	}
	return (vars);
}
void f(void){system("leaks cub3D");}

// Put ONE pixel on screen
void my_pixel_put(mlx_image_t *img, int x, int y, uint32_t color)
{
    img->pixels[y * img->width + x] = color;
}

// Fill screen: TOP=ceiling, BOTTOM=floor
void draw_floor_ceiling(t_cub *cub)
{
    int y;
    
    // Top half = ceiling color (your earth_color)
    y = 0;
    while (y < HEIGHT / 2)
    {
        int x = 0;
        while (x < WIDTH)
            my_pixel_put(cub->img, x++, y, cub->vars.earth_color);
        y++;
    }
    
    // Bottom half = floor color (your floor_color)  
    while (y < HEIGHT)
    {
        int x = 0;
        while (x < WIDTH)
            my_pixel_put(cub->img, x++, y, cub->vars.floor_color);
        y++;
    }
}

int main(int ac, char **av)
{
	atexit(f);
    t_cub cub;
    
    // YOUR PARSING
    cub.vars = parcing(ac, av);
	printf("Floor: 0x%X, Ceiling: 0x%X\n", cub.vars.floor_color, cub.vars.earth_color);
    
    // MLX42 - CORRECT API
    cub.mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
    if (!cub.mlx)
        Error("==> MLX42 init failed");
        
    cub.img = mlx_new_image(cub.mlx, WIDTH, HEIGHT);
    if (!cub.img)
		Error("==> Image creation failed");
	printf("MLX42 window created!\n");
	mlx_key_hook(cub.mlx, &key_hook, cub.mlx);
		
    draw_floor_ceiling(&cub);
	
    // // Player position
    // cub.posX = 2.5;
	// cub.posY = 2.5;
    // // Direction vector
    // cub.dirX = -1.0;
	// cub.dirY = 0.0;
	// // Camera plane
    // cub.planeX = 0.0;
	// cub.planeY = 0.66;
	
    
    mlx_image_to_window(cub.mlx, cub.img, 0, 0);
    mlx_loop(cub.mlx);
    
    mlx_terminate(cub.mlx);
    return (0);
}