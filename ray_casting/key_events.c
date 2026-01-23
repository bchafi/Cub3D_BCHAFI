# include "../parcing.h"

void    rotate_player(t_unit *p, int i)
{
    double oldDirX;
    double oldPlaneX;
    double speed;

    if (i == 1) // Rotate Right
        speed = p->rot_speed;
    else // Rotate Left
        speed = -p->rot_speed;

    // Rotate Direction Vector
    oldDirX = p->dir_x;
    p->dir_x = p->dir_x * cos(speed) - p->dir_y * sin(speed);
    p->dir_y = oldDirX * sin(speed) + p->dir_y * cos(speed);

    // Rotate Camera Plane (Must remain perpendicular to direction!)
    oldPlaneX = p->plane_x;
    p->plane_x = p->plane_x * cos(speed) - p->plane_y * sin(speed);
    p->plane_y = oldPlaneX * sin(speed) + p->plane_y * cos(speed);
}
void    move_forward_back(t_unit *p, int direction) // 1 = Fwd, -1 = Back
{
    double speed = p->move_speed * direction;

    // Check X direction: If next spot is empty, move X
    if (p->map[(int)p->pos_y][(int)(p->pos_x + p->dir_x * speed)] != '1')
        p->pos_x += p->dir_x * speed;
        
    // Check Y direction: If next spot is empty, move Y
    if (p->map[(int)(p->pos_y + p->dir_y * speed)][(int)p->pos_x] != '1')
        p->pos_y += p->dir_y * speed;
}

void    move_strafe(t_unit *p, int direction) // 1 = Right, -1 = Left
{
    double speed = p->move_speed * direction;
    
    // Strafe is perpendicular to direction. 
    // Right vector is (dir_y, -dir_x)
    // Left vector is (-dir_y, dir_x)
    
    // Check X (using plane vector roughly approximates strafing or verify perpendicular math)
    // Better Standard Strafe Math:
    // New X = pos_x + plane_x * speed
    // New Y = pos_y + plane_y * speed
    
    if (p->map[(int)p->pos_y][(int)(p->pos_x + p->plane_x * speed)] != '1')
        p->pos_x += p->plane_x * speed;
        
    if (p->map[(int)(p->pos_y + p->plane_y * speed)][(int)p->pos_x] != '1')
        p->pos_y += p->plane_y * speed;
}

void    move_player(t_unit *p)
{
    if (p->Key_W) move_forward_back(p, 1);
    if (p->Key_S) move_forward_back(p, -1);
    if (p->Arrow_Right) rotate_player(p, 1);
    if (p->Arrow_Left) rotate_player(p, 0);
    
    // Bonus: Strafe
    if (p->Key_D) move_strafe(p, 1);
    if (p->Key_A) move_strafe(p, -1);
}


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
