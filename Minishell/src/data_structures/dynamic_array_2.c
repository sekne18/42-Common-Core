/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:08:19 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 14:17:40 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dyn_arr	*new_dyn_arr(size_t start_size, size_t elem_size)
{
	t_dyn_arr	*arr;

	if (!start_size)
		start_size = 1;
	arr = malloc(sizeof(t_dyn_arr));
	if (!arr || start_size > ((size_t)-1) / elem_size)
		return (NULL);
	arr->data = malloc(elem_size * start_size);
	if (!arr->data)
	{
		free(arr);
		return (NULL);
	}
	arr->max_size = start_size;
	arr->curr_size = 0;
	arr->elem_size = elem_size;
	arr->front = 0;
	return (arr);
}

void	destroy_dyn_arr(t_dyn_arr *arr, void (*destroy_elem)(void *))
{
	size_t	i;

	if (!arr)
		return ;
	if (!destroy_elem)
	{
		free(arr->data);
		free(arr);
		return ;
	}
	i = 0;
	while (i < arr->curr_size)
	{
		destroy_elem(*(void **)((unsigned char *)arr->data
				+ get_real_index(arr, i) * arr->elem_size));
		i++;
	}
	free(arr->data);
	free(arr);
}

void	clear_dyn_arr(t_dyn_arr *arr, void (*destroy_elem)(void *))
{
	size_t	i;

	if (!destroy_elem)
	{
		arr->curr_size = 0;
		arr->front = 0;
		return ;
	}
	i = 0;
	while (i < arr->curr_size)
	{
		destroy_elem(*(void **)((unsigned char *)arr->data
				+ get_real_index(arr, i) * arr->elem_size));
		i++;
	}
	arr->curr_size = 0;
	arr->front = 0;
}

static size_t	min(size_t x, size_t y)
{
	if (x < y)
		return (x);
	return (y);
}

int	enlarge_array(t_dyn_arr *arr, int mult)
{
	void	*new;
	size_t	offset;

	if (arr->elem_size > ((size_t)-1) / mult || arr->curr_size > ((size_t)-1)
		/ (arr->elem_size * mult))
		return (0);
	new = malloc(arr->curr_size * arr->elem_size * mult);
	offset = min(arr->max_size - arr->front, arr->curr_size);
	if (!ft_memcpy(new, (unsigned char *)arr->data + arr->front
			* arr->elem_size, offset * arr->elem_size)
		|| !ft_memcpy((unsigned char *)new + offset, arr->data, arr->curr_size
			* arr->elem_size - offset * arr->elem_size))
		return (0);
	free(arr->data);
	arr->data = new;
	arr->max_size = arr->curr_size * mult;
	return (1);
}
