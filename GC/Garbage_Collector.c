/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Garbage_Collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mir <sel-mir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 03:15:24 by sel-mir           #+#    #+#             */
/*   Updated: 2026/01/05 19:49:47 by sel-mir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		write (2, "Allocation Failure !", 21);
		ft_free(NULL, FATAL);
	}
	ft_free(ptr, 0);
	return (ptr);
}

void	free_textures(t_unit *dataa)
{
	static t_unit	*data;
	int				i;

	i = 0;
	if (!data)
	{
		data = dataa;
		return ;
	}
	while (i < 4)
	{
		if (data->texture[i].texture_img)
		{
			mlx_destroy_image(data->mlx, data->texture[i].texture_img);
			data->texture[i].texture_img = NULL;
		}
		i++;
	}
}

void	quiting(t_unit *data, t_gcollct *head, int flag)
{
	free_textures(NULL);
	ft_free_alls((*data).map_s);
	wipe_all(head);
	if (flag == FATAL)
		exit(1);
	else
		exit(0);
}

//	This Function handles the freeing and the Addresses Savery Avoiding Leaks !

void	ft_free(void *ptr, int flag)
{
	static t_gcollct	*last;
	static t_gcollct	*head;
	t_unit				*data;

	data = holder(NULL);
	if (!head && ptr)
	{
		last = malloc(sizeof(t_gcollct));
		(*last).ptr = ptr;
		(*last).next = NULL;
		return (head = last, (void)0);
	}
	if (!ptr && (flag == FREE_ALL || flag == FATAL))
		quiting(data, head, flag);
	else
	{
		(*last).next = malloc(sizeof(t_gcollct));
		(1) && (last = (*last).next, (*last).ptr = ptr, (*last).next = NULL);
	}
}

void	wipe_all(t_gcollct *head)
{
	t_gcollct	*hold;

	while (head)
	{
		free((*head).ptr);
		hold = head;
		head = (*head).next;
		free(hold);
	}
}
