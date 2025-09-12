/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:19:09 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/12 01:29:27 by bchafi           ###   ########.fr       */
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

typedef struct kval
{
    char *key;
    char *value;
}   t_kval;

typedef struct var
{
    int     line_lines;
    char    **read_file;
    char    *NO;
    char    *SO;
    char    *WE;
    char    *EA;
	char    *F;
	char    *C;
    int     map_index;
    t_kval *keyval;
    int     count_rgb;
    char    **rgb_out;
    int     floor_color;
    int     earth_color;
    
}   t_var;




int     check_file(char *arg);
void    free2D(char **array);
void    read2D(char **array, int len);
char    **get_map(int fd, char *arg, t_var *vars);
int     is_seeing(char **file_line, char *side, int end, int flag);
t_var   *check_sides_tex(char **file_line, t_var *vars);
int     check_tex(t_var *var, char *line);
char	**ft_split(char const *s, char c, t_var *var);
void    free_textures(t_var *vars);

#endif