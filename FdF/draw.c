/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:45:25 by jsekne            #+#    #+#             */
/*   Updated: 2024/11/20 16:45:48 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	connect_horizontal(t_point ***points, int x, int y, t_vars *vars)
{
	t_point	p1;
	t_point	p2;
	int		dx;
	int		dy;
	int		zoom;

	zoom = vars->zoom;
	p1.x = projected_x(points[y][x], zoom, vars) + (WIN_WIDTH / 2);
	p1.y = projected_y(points[y][x], zoom, vars) + (WIN_HEIGHT / 2);
	p2.x = projected_x(points[y][x + 1], zoom, vars) + (WIN_WIDTH / 2);
	p2.y = projected_y(points[y][x + 1], zoom, vars) + (WIN_HEIGHT / 2);
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (abs(dx) > abs(dy))
		slope_less_then_one(&p1, &p2, vars, points[y][x + 1]->z * zoom);
	else
		slope_bigger_than_one(&p1, &p2, vars, points[y][x + 1]->z * zoom);
}

void	connect_vertical(t_point ***points, int x, int y, t_vars *vars)
{
	t_point	p1;
	t_point	p2;
	int		dx;
	int		dy;
	int		zoom;

	zoom = vars->zoom;
	p1.x = projected_x(points[y][x], zoom, vars) + (WIN_WIDTH / 2);
	p1.y = projected_y(points[y][x], zoom, vars) + (WIN_HEIGHT / 2);
	p2.x = projected_x(points[y + 1][x], zoom, vars) + (WIN_WIDTH / 2);
	p2.y = projected_y(points[y + 1][x], zoom, vars) + (WIN_HEIGHT / 2);
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (abs(dx) > abs(dy))
		slope_less_then_one(&p1, &p2, vars, points[y + 1][x]->z * zoom);
	else
		slope_bigger_than_one(&p1, &p2, vars, points[y + 1][x]->z * zoom);
}

void	draw_wireframe(t_point ***points, t_vars *vars)
{
	int	x;
	int	y;
	int	rows;
	int	cols;

	rows = points[0][0]->info->rows;
	cols = points[0][0]->info->cols;
	ft_clear_image(vars, cols, rows);
	transform_points(points, vars);
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
		if ((a->x <= WIN_WIDTH && a->x >= 0) && (a->y <= WIN_HEIGHT
				&& a->y >= 0))
			my_mlx_pixel_put(vars->data, a->x, a->y,
				interpolate_color(vars->min_z, vars->max_z, z));
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
		if ((a->x <= WIN_WIDTH && a->x >= 0) && (a->y <= WIN_HEIGHT
				&& a->y >= 0))
			my_mlx_pixel_put(vars->data, a->x, a->y,
				interpolate_color(vars->min_z, vars->max_z, z));
		a->y += sy;
		if (p >= 0)
		{
			a->x += sx;
			p -= 2 * dy;
		}
		p += 2 * dx;
	}
}
