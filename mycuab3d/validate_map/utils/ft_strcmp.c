/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:21:47 by yrhandou          #+#    #+#             */
/*   Updated: 2025/09/08 10:01:02 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s1[i])
	{
		if ((unsigned char)s1[i] != (unsigned char )s2[i])
			return ((unsigned char)s1[i] - (unsigned char )s2[i]);
		i++;	
	}
	return (0);
}
