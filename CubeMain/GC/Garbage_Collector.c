/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Garbage_Collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkali <bkali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 03:15:24 by sel-mir           #+#    #+#             */
/*   Updated: 2026/01/01 01:23:48 by bkali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cub3d.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		int a = write (2,"Allocation Failure !", 21);
		if (a)
			a = 1;
		ft_free(NULL, FATAL);
	}
	ft_free(ptr, 0);
	return (ptr);
}

void	free_textures(t_unit *dataa)
{
	static t_unit *data;
	int i;
	
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

//	This Function handles the freeing and the Addresses Savery Avoiding Leaks !

void	ft_free(void *ptr, int flag)
{
	static t_gcollct	*last;
	static t_gcollct	*head;

	
	if (!head && ptr)
	{
		last = malloc(sizeof(t_gcollct));
		(*last).ptr = ptr;
		(*last).next = NULL;
		head = last;
		return ;
	}
	if (!ptr && (flag == FREE_ALL || flag == FATAL))
	{
		free_textures(NULL);
		wipe_all(head), (last = NULL);
		if (flag == FATAL)
			exit(1);
		else
			exit(0);
	}
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

//	This Function Looks for the strcut that has the same pointer passed
//	to it and returns the struct 

void	search_gcollct(t_gcollct *head, void *ptr, t_gcollct **ret)
{
	t_gcollct	*before;
	t_gcollct	*next;

	next = NULL;
	before = NULL;
	while (head)
	{
		if ((*head).ptr == ptr)
		{
			ret[0] = before;
			ret[1] = head;
			ret[2] = next;
			return ;
		}
		before = head;
		head = (*head).next;
		if (head)
			next = (*head).next;
		else if (!head)
			next = NULL;
	}
}
