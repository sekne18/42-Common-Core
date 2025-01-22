/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:47:06 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 14:16:34 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * always give the element you want to add by reference
 * for example:
 * 1) if you want an array of int's give int *
 * 2) if you want an array of int *'s give int **
 * 3) if you want to have an entry that is all zeros give NULL
 */
int	push_back(t_dyn_arr *arr, void *elem)
{
	if (arr->curr_size == arr->max_size && !enlarge_array(arr, 2))
		return (0);
	if (!elem)
		ft_memset((unsigned char *)arr->data + get_real_index(arr,
				arr->curr_size) * arr->elem_size, 0, arr->elem_size);
	else
		ft_memcpy(((unsigned char *)arr->data) + get_real_index(arr,
				arr->curr_size) * arr->elem_size, elem, arr->elem_size);
	arr->curr_size++;
	return (1);
}

/*

    * this function will return a pointer to the front element in the array if
 it exists

    * make sure to copy the dereferenced value of this pointer since other
 changes to the dynamic array
 * could mutate the field in the array
 */
void	*pop_front(t_dyn_arr *arr)
{
	void	*elem;

	if (!arr->curr_size)
		return (NULL);
	elem = (unsigned char *)arr->data + arr->front * arr->elem_size;
	if (arr->curr_size == 1)
		arr->front = 0;
	else
		arr->front = get_real_index(arr, 1);
	arr->curr_size--;
	return (elem);
}

/*

    * this function will replace the element at the given index with the given
 element
 * if the index is out of bounds the function will fail and return 0

    * if the destroy_elem function is given it will be called on the element
 being replaced
 * if the element is successfully replaced it will return 1
 */
int	replace(t_dyn_arr *arr, void *elem, size_t index,
		void (*destroy_elem)(void *))
{
	if (index >= arr->curr_size)
		return (0);
	if (destroy_elem)
		destroy_elem(*(void **)((unsigned char *)arr->data
				+ get_real_index(arr, index) * arr->elem_size));
	ft_memcpy(arr->data + get_real_index(arr, index) * arr->elem_size, elem,
		arr->elem_size);
	return (1);
}

void	insert(t_dyn_arr *arr, size_t i, void *elem)
{
	size_t	j;

	if (i >= arr->curr_size)
		return ;
	j = arr->curr_size;
	push_back(arr, NULL);
	while (j > i)
	{
		replace(arr, get_val(arr, j - 1), j, NULL);
		j--;
	}
	replace(arr, elem, i, NULL);
}
