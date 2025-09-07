/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 08:52:00 by yrhandou          #+#    #+#             */
/*   Updated: 2025/08/28 12:34:56 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_int_array(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putendl_fd(ANSI_COLOR_RED "Failure: Empty Array", 2), FAIL);
	while (s[i])
	{
		if (!ft_is_int(s[i]))
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
