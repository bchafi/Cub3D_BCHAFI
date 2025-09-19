/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:19:09 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/19 10:33:24 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "utils/get_next_line/get_next_line.h"
#include "utils/libft/libft.h"
#include "utils/ft_printf/ft_printf.h"


#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define reset "\e[0m"

typedef struct kval
{
    char *key;
    char *value;
}   t_kval;

typedef struct var
{
    int				len_lines;
    char			**read_file;
    char			*NO;
    char			*SO;
    char			*WE;
    char			*EA;    
    int				floor_color;
    int             map_index;
    unsigned int    earth_color;
    unsigned int    count_rgb;
    char            *tmp_r;
    char            *tmp_g;
    char            *tmp_b;
    int             lines_map;
    char            **map;
    int             len_width;
    char            **map_s;
}   t_var;
// Parsing.c
void    Error(char *str);
void    free2D(char **array);
int     check_file(char *arg);
void    read2D(char **array, int len);
char    **get_full_file(int fd, char *arg, t_var *vars);

// Funciton_out.c
t_var   *initial_state(t_var *vars);
void    free_textures(t_var *vars);
void    Error(char *str);
void    free2D(char **array);
int     is_seeing(char **file_line, char *side, int end, int n);
void    Valid(t_var *vars); //
 
// configuration_tools.c
int     is_line_map(char *file_line);
int     handle_texture_line(t_var *vars, char **file_line, char *trimed, int i);
int     handle_color_line(t_var *vars, char **file_line, char *trimed, int i);
int     type_file_line(t_var *vars, char **file_line, char *trimed, int i, int *len);
int     check_file_lines(char **file_line, t_var *vars, int *len);

// check_configur.c
int     check_tex(t_var *var, char *line);
int     check_isnum(char *rgb_num);
int     valide_Color(char **rgb);
int     store_rgb(t_var *var, int is_floor, char **slice_rgb);
int     check_color(t_var *var, char *line, int is_floor);
t_var   *check_configuration(char **file_line, t_var *vars);

// map.c
char    **find_valid_map(t_var *vars);
char    *multi_space(int len);
char    **get_map(t_var *vars, char **file, int start);
int     find_map_start(char **file);
char    **map_copy_s(t_var *var, char **map);


// funciton
char	**ft_split(char const *s, char c, t_var *var);




#endif