/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:34:54 by bchafi            #+#    #+#             */
/*   Updated: 2026/01/15 05:52:31 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCING_H
#define PARCING_H

#ifndef O_DIRECTORY
# define O_DIRECTORY 0x10000
#endif

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include "utils/get_next_line/get_next_line.h"
#include "utils/libft/libft.h"
 
#define ROSE "\e[0;31m"
#define GRN "\e[0;32m"  
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define reset "\e[0m"

typedef struct s_unit t_unit;

typedef struct kval
{
    char *key;
    char *value;
}   t_kval;

typedef struct var
{
    int				len_lines;
    char			**read_file;
    char			*north;
    char			*south;
    char			*west;
    char			*east;
    char            direction;
    int             x;
    int             y;
    int             map_index;
    uint32_t        floor_color;
    uint32_t        earth_color;
    char*           tmp_a;
    char*           tmp_b;
    char*           tmp_c;
    int             count_rgb;
    int             lines_map;
    char            **map;
    int             len_width;
    char            **map_s;
    int             len_cline;
}   t_var;

// Parsing functions
int     check_tex(t_var *var, char *line);
int     check_isnum(char *rgb_num);
int     valide_color(char **rgb);
int     store_rgb(t_var *var, int is_floor, char **slice_rgb);
int     check_color(t_var *var, char *line, int is_floor);
t_var   *check_configuration(char **file_line, t_var *vars);
int     checks(int fd, t_var *vars, char *av);
int     is_line_map(char *file_line);
int     handle_texture_line(t_var *vars, char **file_line, char *trimed, int i);
int     handle_color_line(t_var *vars, char **file_line, char *trimed, int i);
int     type_file_line(t_var *vars, char **file_line, char *trimed, int i);
int     check_file_lines(char **file_line, t_var *vars);
char    **get_map(t_var *vars, char **file, int start);
void    free_partial_map(char **map, int i);
char    **ft_other_split(char const *s, char c, t_var *var);
char    **ft_split(char const *s, char c, t_var *var);
t_var   *initial_state(t_var *vars);
void    free_texture(t_var *vars);
int     is_seeing(char **file_line, char *side, int end, int n);
char    *multi_space(int len);
int     find_map_start(char **file);
char    **get_map(t_var *vars, char **file, int start);
char    **map_copy_s(t_var *var, char **map);
int     find_valid_map(t_var *vars);
void    error(char *str);
void    free2d(char **array);
int     check_file(char *arg);
char    **get_full_file(int fd, char *arg, t_var *vars);
int     is_valid_char(char c);
int     validate_map(t_var *vars);
t_var   *parcing(int ac, char **av);
void    ft_free_alls(t_var *vars, t_unit *player);

// Raycasting functions

# include <math.h>
# include <limits.h>
# include <float.h>
# include "./mlx_linux/mlx.h"

#  define HEIGHT 768
#  define WIDTH 1024
#  define CUBE_DIM 64
#  define ESCP 65307
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define ARROW_RIGHT 65363
#  define ARROW_LEFT 65361
#  define CUBE 60
#  define FOV 70.0 // Field of View in degrees
#  define PI 3.14159265358979323846

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}   t_img;

typedef struct s_unit
{
    double      move_speed;
    double      rot_speed;
    double      pos_x;
    double      pos_y;      
    double      dir_x;
    double      dir_y;      
    double      plane_x;
    double      plane_y;
    double      angle_b_ray;
    double      proj_plane_dist;
    double      v_angle;
    char       **map;
    void        *mlx;
    void        *win;
    t_img       img;
    t_img       screen;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    int         Key_W;
    int         Key_A;
    int         Key_S;
    int         Key_D;
    int         Arrow_Right;
    int         Arrow_Left;
    t_img       tex[4];
    
}	t_unit;

void    raycast_engine(t_var *vars);
int     init_mlx(t_unit *core);
void    init_player(t_unit *data, t_var *vars);
int     main_work(t_unit *player);
int     close_window(t_unit *player);
int     key_press(int keycode, t_unit *vars);
int     key_release(int keycode, t_unit *vars);
void    load_one_texture(t_unit *p, int idx, char *path);
void    init_textures(t_unit *p, t_var *vars);
void    my_mlx_pixel_put(t_unit *data, int x, int y, int color);
void    load_one_texture(t_unit *p, int i, char *path);
void    init_textures(t_unit *p, t_var *vars);
int     get_texture_color(t_img *tex, int x, int y);


#endif