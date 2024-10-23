/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:45:25 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/23 16:56:52 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_point p1, t_point p2, t_data *img)
{
	int		x;
	int		y;
	int		steps;
	int		x_inc;
	int		y_inc;

	if (abs(p2.x - p1.x) > abs(p2.y - p1.y))
		steps = abs(p2.x - p1.x);
	else
		steps = abs(p2.y - p1.y);
	x_inc = (p2.x - p1.x) / (float)steps;
    y_inc = (p2.y - p1.y) / (float)steps;
	x = p1.x;
	y = p1.y;
	while (0 <= steps)
	{
		my_mlx_pixel_put(img, round(x), round(y), 0x00FF0000);
		x += x_inc;
		y += y_inc;
	}
}

void	connect_horizontal(t_point ***points, int x, int y, t_data *img)
{
	t_point p1;
	t_point p2;

	p1.x = projected_x(points[y][x]);
	p1.y = projected_y(points[y][x]);
	p2.x = projected_x(points[y][x + 1]);
	p2.y = projected_y(points[y][x + 1]);
	draw_line(p1, p2, img);
}

void	connect_vertical(t_point ***points, int x, int y, t_data *img)
{
	t_point p1;
	t_point p2;

	p1.x = projected_x(points[y][x]);
	p1.y = projected_y(points[y][x]);
	p2.x = projected_x(points[y][x + 1]);
	p2.y = projected_y(points[y][x + 1]);
	draw_line(p1, p2, img);
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
			// Draw horizontal line to right neighbor if it exists
			if (x < cols - 1)
				connect_horizontal(points, x, y, img);
			// Draw vertical line to bottom neighbor if it exists
			if (y < rows - 1)
				connect_vertical(points, x, y, img);
			x++;
		}
		y++;
	}
}
