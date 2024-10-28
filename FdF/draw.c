/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:45:25 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/28 19:16:32 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	connect_horizontal(t_point ***points, int x, int y, t_vars *vars)
{
	t_point	p1;
	t_point	p2;
	int		dx;
	int		dy;
	int		scale;

	scale = 9;
	p1.x = projected_x(points[y][x], scale) + (WIN_WIDTH / 2);
	p1.y = projected_y(points[y][x], scale) + (WIN_HEIGHT / 2);
	p2.x = projected_x(points[y][x + 1], scale) + (WIN_WIDTH / 2);
	p2.y = projected_y(points[y][x + 1], scale) + (WIN_HEIGHT / 2);
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (abs(dx) > abs(dy))
		slope_less_then_one(&p1, &p2, vars, points[y][x + 1]->z * scale);
	else
		slope_bigger_than_one(&p1, &p2, vars, points[y][x + 1]->z * scale);
}

void	connect_vertical(t_point ***points, int x, int y, t_vars *vars)
{
	t_point	p1;
	t_point	p2;
	int		dx;
	int		dy;
	int		scale;

	if ((WIN_WIDTH / points[0][0]->info->cols) <
		(WIN_HEIGHT / points[0][0]->info->rows))
		scale = WIN_WIDTH / points[0][0]->info->cols;
	else
		scale = WIN_HEIGHT / points[0][0]->info->rows;
	scale /= 10;
	scale++;
	p1.x = projected_x(points[y][x], scale) + (WIN_WIDTH / 2);
	p1.y = projected_y(points[y][x], scale) + (WIN_HEIGHT / 2);
	p2.x = projected_x(points[y + 1][x], scale) + (WIN_WIDTH / 2);
	p2.y = projected_y(points[y + 1][x], scale) + (WIN_HEIGHT / 2);
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (abs(dx) > abs(dy))
		slope_less_then_one(&p1, &p2, vars, points[y + 1][x]->z * scale);
	else
		slope_bigger_than_one(&p1, &p2, vars, points[y + 1][x]->z * scale);
}

void	draw_wireframe(t_point ***points, t_vars *vars)
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
			if (x < cols - 1)
				connect_horizontal(points, x, y, vars);
			if (y < rows - 1)
				connect_vertical(points, x, y, vars);
			x++;
		}
		y++;
	}
}

void	slope_less_then_one(t_point *a, t_point *b, t_vars *vars, int z)
{
	int	sx;
	int	sy;
	int	p;
	int	dx;
	int	dy;

	dx = abs(b->x - a->x);
	dy = abs(b->y - a->y);
	set_setters(a, b, &sy, &sx);
	p = 2 * dx - dx;
	while (a->x != b->x)
	{
		my_mlx_pixel_put(vars->data, a->x, a->y, interpolate_color(vars->min_z,
				vars->max_z, z));
		a->x += sx;
		if (p >= 0)
		{
			a->y += sy;
			p -= 2 * dx;
		}
		p += 2 * dy;
	}
}

void	slope_bigger_than_one(t_point *a, t_point *b, t_vars *vars, int z)
{
	int	sx;
	int	sy;
	int	p;
	int	dx;
	int	dy;

	dx = abs(b->x - a->x);
	dy = abs(b->y - a->y);
	set_setters(a, b, &sy, &sx);
	p = 2 * dx - dy;
	while (a->y != b->y)
	{
		my_mlx_pixel_put(vars->data, a->x, a->y, interpolate_color(vars->min_z,
				vars->max_z, z));
		a->y += sy;
		if (p >= 0)
		{
			a->x += sx;
			p -= 2 * dy;
		}
		p += 2 * dx;
	}
}
