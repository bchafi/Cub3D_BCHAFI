/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pixel_Draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 18:32:41 by sel-mir           #+#    #+#             */
/*   Updated: 2026/01/03 18:33:09 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	write_pixel(t_unit *data, int x, int y, int color)
{
	char	*dst;

	dst = (*data).addr + (y
			* (*data).line_length + x * ((*data).bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	safe_pixel_write(t_unit *data, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	write_pixel(data, x, y, color);
}
