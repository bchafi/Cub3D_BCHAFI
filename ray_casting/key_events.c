# include "../parcing.h"

int    close_window(t_unit *player)
{
    if (player)
    {
        if (player->screen.img)
            mlx_destroy_image(player->mlx, player->screen.img);
        if (player->win)
            mlx_destroy_window(player->mlx, player->win);
        if (player->mlx)
            free(player->mlx);
    }
    printf("Window closed successfully.\n");
    exit(0);
    return (0);
}

int	key_press(int keycode, t_unit *vars)
{
	if (keycode == ESCP)
		close_window(vars);
	if (keycode == W_KEY)
		vars->Key_W = 1;
	if (keycode == S_KEY)
		vars->Key_S = 1;
	if (keycode == A_KEY)
		vars->Key_A = 1;
	if (keycode == D_KEY)
		vars->Key_D = 1;
	if (keycode == ARROW_LEFT)
		vars->Arrow_Left = 1;
	if (keycode == ARROW_RIGHT)
		vars->Arrow_Right = 1;
    printf("Key pressed: %d\n", keycode);
	return (0);
}

int	key_release(int keycode, t_unit *vars)
{
	if (keycode == W_KEY)
		vars->Key_W = 0;
	if (keycode == S_KEY)
		vars->Key_S = 0;
	if (keycode == A_KEY)
		vars->Key_A = 0;
	if (keycode == D_KEY)
		vars->Key_D = 0;
	if (keycode == ARROW_LEFT)
		vars->Arrow_Left = 0;
	if (keycode == ARROW_RIGHT)
		vars->Arrow_Right = 0;
    printf("Key released: %d\n", keycode);
	return (0);
}

