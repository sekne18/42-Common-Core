/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 07:25:34 by jsekne            #+#    #+#             */
/*   Updated: 2024/11/21 14:03:47 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
void	rotate_points(t_point **points, t_vars *vars)
{
	int	x;
	int	y;
	int	rows;
	int	cols;

	rows = points[0][0]->info->rows;
	cols = points[0][0]->info->cols;
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			rotate_x(points[y][x], vars->angle_x);
			rotate_y(points[y][x], vars->angle_y);
			rotate_z(points[y][x], vars->angle_z);
			x++;
		}
		y++;
	}
}

void rotate_z(t_point *a, float angle)
{
	int tmp;

	tmp = a->x;
	a->x = tmp * cos(angle) - a->y * sin(angle);
	a->y = tmp * sin(angle) + a->y * cos(angle);
}

void rotate_y(t_point *a, float angle)
{
	int tmp;

	tmp = a->x;
	a->x = tmp * cos(angle) + a->z * sin(angle);
	a->z = a->z * cos(angle) - tmp * sin(angle);
}

void rotate_x(t_point *a, float angle)
{
	int tmp;

	tmp = a->y;
	a->y = tmp * cos(angle) - a->z * sin(angle);
	a->z = tmp * sin(angle) + a->z * cos(angle);
}*/
