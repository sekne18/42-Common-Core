/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:10:02 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/25 15:55:32 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	fraction(int x, int y, t_point *a, t_point *b)
{
	int   dx;
	int   dy;
	float fract;
	

	dx = b->x - a->x;
	dy = b->y - a->y;
	if (abs(dx) > abs(dy))
		if (a->x != b->x)
			fract = ((x - a->x) / (b->x - a->x));
		else
			fract = 0;
	else
		if (a->y != b->y)
			fract = ((y - a->y) / (b->y - a->y));
		else
			fract = 0;
	return fract;
}
