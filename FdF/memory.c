/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:18:50 by jsekne            #+#    #+#             */
/*   Updated: 2024/11/26 12:19:30 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	**allocate_points(int len_x)
{
	t_point	**point_arr;

	point_arr = malloc((len_x + 1) * sizeof(t_point *));
	if (point_arr)
		point_arr[len_x] = NULL;
	return (point_arr);
}
