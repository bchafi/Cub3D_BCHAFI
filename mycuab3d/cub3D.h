/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:19:09 by bchafi            #+#    #+#             */
/*   Updated: 2025/09/08 10:19:11 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "validate_map/utils/ft_printf.a"
#include "validate_map/utils/get_next_line.a"
#include "validate_map/utils/libft.a"


typedef struct var
{
    int line_lines;
}   t_var;


int     check_file(char *arg);
char	**get_map(int fd, char *arg, t_var *vars);
int     ft_strcmp(const char *s1, const char *s2);


#endif