/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncasecmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:37:07 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/27 11:53:59 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strncasecmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if(!s1 && !s2)
		return (0);
	i = 0;
	while (1)
	{
		if(s1[i] == s2[i] || s1[i] == (s2[i] +32))
	}
}
