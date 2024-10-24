/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:45:25 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/24 23:01:55 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	connect_horizontal(t_point ***points, int x, int y, t_data *img)
{
	t_point p1;
	t_point p2;
	int		dx;
	int		dy;

	p1.x = projected_x(points[y][x]) + (WIN_WIDTH / 4);
	p1.y = projected_y(points[y][x]) + (WIN_HEIGHT / 4);
	p2.x = projected_x(points[y][x + 1]) + (WIN_WIDTH / 4);
	p2.y = projected_y(points[y][x + 1]) + (WIN_HEIGHT / 4);
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (abs(dx) > abs(dy))
		slope_less_then_one(&p1, &p2, img);
	else
		slope_bigger_than_one(&p1, &p2, img);
}

void	connect_vertical(t_point ***points, int x, int y, t_data *img)
{
	t_point p1;
	t_point p2;
	int		dx;
	int		dy;

	p1.x = projected_x(points[y][x]) + (WIN_WIDTH / 4);
	p1.y = projected_y(points[y][x]) + (WIN_HEIGHT / 4);
	p2.x = projected_x(points[y + 1][x]) + (WIN_WIDTH / 4);
	p2.y = projected_y(points[y + 1][x]) + (WIN_HEIGHT / 4);
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (abs(dx) > abs(dy))
		slope_less_then_one(&p1, &p2, img);
	else
		slope_bigger_than_one(&p1, &p2, img);
}

void	draw_wireframe(t_point ***points, t_data *img)
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
				connect_horizontal(points, x, y, img);
			if (y < rows - 1)
				connect_vertical(points, x, y, img);
			x++;
		}
		y++;
	}
}

int projected_x(t_point *p)
{
	return (((p->x - p->y) * cos(0.523599)) * 2);
}

int projected_y(t_point *p)
{
	return (((p->x + p->y) * sin(0.523599) - p->z) * 2);
}

void slope_less_then_one(t_point *a, t_point *b, t_data *img)
{
	int p;
	int i;
	int	dx;
	int	dy;

	dx = b->x - a->x;
	dy = b->y - a->y;
	i = -1;
	p = 2 * abs(dy) - abs(dx);
	while (++i < abs(dx))
	{
		if (dx > 0)
			a->x += 1;
		else
			a->x -= 1;
		if (p < 0)
			p = p + 2 * abs(dy);
		else
		{
			if (dy > 0)
				a->y += 1;
			else
				a->y -= 1;
			p = p + 2 * abs(dy) - 2 * abs(dx);
		}
		my_mlx_pixel_put(img, a->x, a->y, 0x00FFFFFF);
	}
}

void slope_bigger_than_one(t_point *a, t_point *b, t_data *img)
{
	int p;
	int i;
	int	dx;
	int	dy;
	
	dx = b->x - a->x;
	dy = b->y - a->y;
	i = 0;
	p = 2 * dx - dy;
	my_mlx_pixel_put(img, a->x, a->y, 0x00FFFFFF);
	while (i < dy)
	{
		a->y += 1;
		if (p < 0)
			p = p + 2 * dx;
		else
		{
			a->x += 1;
			p = p + 2 * dx - 2 * dy;
		}
		my_mlx_pixel_put(img, a->x, a->y, 0x00FFFFFF);
		i++;
	}
}
