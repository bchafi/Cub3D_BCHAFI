/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 10:48:59 by yrhandou          #+#    #+#             */
/*   Updated: 2025/08/27 10:26:16 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3D.h"
#include "include/parcing.h"

void draw_rectangle(t_cube *cub, t_obj *obj, uint32_t color)
{
	size_t i;
	size_t j;

	i = obj->Ypos;
	j = obj->Xpos;
	while (i < obj->height + obj->Ypos)
	{
		j = obj->Xpos;
		while (j < obj->width + obj->Xpos)
		{
			mlx_put_pixel(cub->img, j, i, color);
			j++;
		}
		i++;
	}
}
void set_obj(t_obj *obj, size_t width, size_t height, size_t Xpos, size_t Ypos)
{
	obj->width = width;
	obj->height = height;
	obj->Xpos = Xpos;
	obj->Ypos = Ypos;
}

void draw_map(t_cube *cub, char **av, int ac)
{
	size_t	i;
	size_t	j;
	char **map;
	t_obj obj;
	uint32_t color;
	t_var vars;
	
	i = 0;
	j = 0;
	if (ac != 2)
	{
		Error("** Uncomplite Argument **");
		exit(1);
	}
	int fd = check_file(av[1]);
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
	map = vars.map;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == '0')
				color = RED;
			else if(ft_is_player(map[i][j]))
				color = BLUE;
			else
				color = GREEN;
			set_obj(&obj, 30, 30, j*32, i*32);
			draw_rectangle(cub, &obj, color);
			j++;
		}
		i++;
	}
}

/**
 * @brief Creates a timer that runs for every frame
 * @param param cube_t *
 */
void timer(void* param)
{
	t_cube *cub;

	cub = (t_cube *)param;
	char buffer[1000];
	sprintf(buffer,"Timer : %f",mlx_get_time());
	if(cub->timer)
		mlx_delete_image(cub->mlx, cub->timer);
	cub->timer = mlx_put_string(cub->mlx,buffer,800,600);
}
void grayify(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	// t_cube *cub;
	// int	x;
	// int	y;
	(void)param;
	// cub = (t_cube *)param;
	 if(button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS && mods == MLX_CONTROL)
	{
		printf("Xpos: %d, Ypos:%d\n", 100,100);
	}
}

void f(void)
{
	system("leaks cub3D");
}
int main(int ac, char **av)
{
	atexit(f);
	t_cube cub;

	if (!cub_init(&cub))
		return 0;
	draw_map(&cub, av, ac);
	mlx_close_hook(cub.mlx, ft_close, &cub);
	mlx_key_hook(cub.mlx, esc_close, &cub);
	mlx_mouse_hook(cub.mlx, grayify,&cub);
	mlx_loop_hook(cub.mlx, timer,&cub);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	return (0);
}
