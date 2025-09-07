/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:06:17 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/27 11:32:52 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strndup(const char *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	if(!s)
		return (NULL);
	str = ft_calloc(sizeof(char), n + 1);
	if(!str)
		return (NULL);
	while(i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return str;
}
