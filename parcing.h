/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:34:54 by bchafi            #+#    #+#             */
/*   Updated: 2026/01/05 17:35:18 by bchafi           ###   ########.fr       */
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
void    ft_free_alls(t_var *vars);

#endif