/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:05:42 by yrhandou          #+#    #+#             */
/*   Updated: 2025/09/03 10:53:26 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

t_vector *create_vector(int i, int j)
{
	t_vector *vec;

	if((i > INT_MAX || i < INT_MIN) || (j > INT_MAX || j < INT_MIN))
		return (NULL);
	vec = ft_calloc(1, sizeof(t_vector));
	if(!vec)
		return (NULL);
	vec->Y = i;
	vec->X = j;
	return vec;
}

t_vector *print_vec(t_vector *vec)
{
	printf("X = %d , Y = %d\n", vec->X, vec->Y);
	return (vec);
}

t_vector *add_vec(t_vector *vec_A, t_vector *vec_B )
{
	t_vector *result;

	result = create_vector(0, 0);
	if(!result)
		return NULL;
	result->X = vec_A->X + vec_B->X;
	result->Y = vec_A->Y + vec_B->Y;
	return (result);
}

t_vector *advance_vec(t_vector *vec, int val)
{
	t_vector *result;

	result = create_vector(0, 0);
	if(!result)
		return NULL;
	result->X = vec->X + val;
	result->Y = vec->Y + val;
	return (result);
}

t_vector *update_vec(t_vector *vec, int x, int y)
{
	vec->X = x;
	vec->Y = y;
	return (vec);
}

t_vector *sub_vec(t_vector *vec_A, t_vector *vec_B )
{
	t_vector *result;

	result = create_vector(0, 0);
	if(!result)
		return NULL;

	result->X = vec_A->X - vec_B->X;
	result->Y = vec_A->Y - vec_B->Y;
	return (result);
}

void clean_vec(t_vector *vec)
{
	vec->X = 0;
	vec->Y = 0;
	free(vec);
}
