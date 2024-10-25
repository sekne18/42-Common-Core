/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:45:25 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/25 14:08:47 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	connect_horizontal(t_point ***points, int x, int y, t_data *img)
{
	t_point p1;
	t_point p2;
	int		dx;
	int		dy;

	p1.x = projected_x(points[y][x]) + (WIN_WIDTH / 2);
	p1.y = projected_y(points[y][x]) + (WIN_HEIGHT / 2);
	p2.x = projected_x(points[y][x + 1]) + (WIN_WIDTH / 2);
	p2.y = projected_y(points[y][x + 1]) + (WIN_HEIGHT / 2);
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

	p1.x = projected_x(points[y][x]) + (WIN_WIDTH / 2);
	p1.y = projected_y(points[y][x]) + (WIN_HEIGHT / 2);
	p2.x = projected_x(points[y + 1][x]) + (WIN_WIDTH / 2);
	p2.y = projected_y(points[y + 1][x]) + (WIN_HEIGHT / 2);
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
	float	rotation;

	rotation = ((M_PI * 30) / 180);
	return (((p->x - p->y) * cos(rotation)) * 2);
}

int projected_y(t_point *p)
{
	float	rotation;

	rotation = ((M_PI * 30) / 180);
	return (((p->x + p->y) * sin(rotation) - p->z) * 2);
}

void slope_less_then_one(t_point *a, t_point *b, t_data *img)
{
    int	sx;
    int	sy;
	int	p;
	int	dx;
	int	dy;

	dx = abs(b->x - a->x);
	dy = abs(b->y - a->y);
	if (a->x < b->x) // Move direction in x
		sx = 1;
	else
		sx = -1;
    if (a->y < b->y) // Move direction in y
		sy = 1;
	else
		sy = -1;
	p = 2 * dx - dx;  // Initial decision variable
    while (a->x != b->x)
    {
        my_mlx_pixel_put(img, a->x, a->y, 0x00FFFFFF);
        a->x += sx;  // Move in y direction
        if (p >= 0)
        {
            a->y += sy;  // Move in x direction when p is non-negative
            p -= 2 * dx;
        }
        p += 2 * dy;  // Always adjust p by 2*dx
    }
}

void slope_bigger_than_one(t_point *a, t_point *b, t_data *img)
{
    int	sx;
    int	sy;
	int	p;
	int	dx;
	int	dy;

	dx = abs(b->x - a->x);
	dy = abs(b->y - a->y);
	if (a->x < b->x) // Move direction in x
		sx = 1;
	else
		sx = -1;
    if (a->y < b->y) // Move direction in y
		sy = 1;
	else
		sy = -1;
	p = 2 * dx - dy;  // Initial decision variable
    while (a->y != b->y)
    {
        my_mlx_pixel_put(img, a->x, a->y, 0x00FFFFFF);
        a->y += sy;  // Move in y direction
        if (p >= 0)
        {
            a->x += sx;  // Move in x direction when p is non-negative
            p -= 2 * dy;
        }
        p += 2 * dx;  // Always adjust p by 2*dx
    }
}
