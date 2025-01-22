/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:11:26 by fmol              #+#    #+#             */
/*   Updated: 2025/01/14 14:18:10 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_real_index(t_dyn_arr *arr, size_t i)
{
	return (i + arr->front % arr->max_size);
}

void	*get_val(t_dyn_arr *arr, size_t i)
{
	if (!arr || i >= arr->curr_size)
		return (NULL);
	return ((unsigned char *)arr->data + get_real_index(arr, i)
		* arr->elem_size);
}
