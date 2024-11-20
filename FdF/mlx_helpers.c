/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:38:31 by jans              #+#    #+#             */
/*   Updated: 2024/11/20 11:25:34 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	projected_x(t_point *p, int scale, t_vars *vars)
{
	/*rotate_x(p, vars->angle_x);
    rotate_y(p, vars->angle_y);
    rotate_z(p, vars->angle_z);*/
	(void)vars;
	return (((p->x * scale) - (p->y * scale)) * cos(M_PI / 6));
}

int	projected_y(t_point *p, int scale, t_vars *vars)
{
	/*rotate_x(p, vars->angle_x);
    rotate_y(p, vars->angle_y);
    rotate_z(p, vars->angle_z);*/
	(void)vars;
	return (((p->x * scale) + (p->y * scale)) * sin(M_PI / 6) - (p->z * scale));
}

void	set_setters(t_point *a, t_point *b, int *sy, int *sx)
{
	if (a->x < b->x)
		*sx = 1;
	else
		*sx = -1;
	if (a->y < b->y)
		*sy = 1;
	else
		*sy = -1;
}

void rotate_x(t_point *p, float angle)
{
    float y = p->y;
    float z = p->z;

    p->y = y * cos(angle) - z * sin(angle);
    p->z = y * sin(angle) + z * cos(angle);
}

void rotate_y(t_point *p, float angle)
{
    float x = p->x;
    float z = p->z;

    p->x = x * cos(angle) + z * sin(angle);
    p->z = -x * sin(angle) + z * cos(angle);
}

void rotate_z(t_point *p, float angle)
{
    float x = p->x;
    float y = p->y;

    p->x = x * cos(angle) - y * sin(angle);
    p->y = x * sin(angle) + y * cos(angle);
}

void	ft_clear_image(t_vars *vars, int cols, int rows)
{
	int	y;
	int x;

	(void)rows;
	(void)cols;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			my_mlx_pixel_put(vars->data, x, y, 0);
	}
}
