/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:10:02 by jsekne            #+#    #+#             */
/*   Updated: 2024/11/25 15:00:59 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	interpolate_color(int min_z, int max_z, int z)
{
	t_color	color_low;
	t_color	color_high;
	float	z_ratio;
	t_color	color;

	z_ratio = 0;
	color_low.r = 0;
	color_low.g = 232;
	color_low.b = 0;
	color_high.r = 252;
	color_high.g = 109;
	color_high.b = 0;
	if (max_z != min_z)
		z_ratio = (float)(z - min_z) / (max_z - min_z);
	if (z_ratio <= 0)
		z_ratio = 0;
	if (z_ratio > 1)
		z_ratio = 1;
	color.r = color_low.r + (color_high.r - color_low.r) * z_ratio;
	color.g = color_low.g + (color_high.g - color_low.g) * z_ratio;
	color.b = color_low.b + (color_high.b - color_low.b) * z_ratio;
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	free_points(t_point ***points, t_vars *vars)
{
	int	x;
	int	y;
	int	rows;
	int	cols;

	cols = vars->info->cols;
	rows = vars->info->rows;
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			free(points[y][x]);
			x++;
		}
		free(points[y]);
		y++;
	}
	free(points);
}

void	cleanup(t_vars *vars)
{
	if (vars)
	{
		if (vars->data)
		{
			if (vars->data->img)
				mlx_destroy_image(vars->mlx, vars->data->img);
			free(vars->data);
		}
		if (vars->win)
			mlx_destroy_window(vars->mlx, vars->win);
		if (vars->mlx)
		{
			mlx_destroy_display(vars->mlx);
			free(vars->mlx);
		}
		if (vars->points)
			free_points(vars->points, vars);
		free(vars);
	}
}

void	transform_points(t_point ***points, t_vars *vars)
{
	int	x;
	int	y;
	int	rows;
	int	cols;

	rows = vars->info->rows;
	cols = vars->info->cols;
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			set_translation(points[y][x], vars);
			x++;
		}
		y++;
	}
}

void	set_translation(t_point *points, t_vars *vars)
{
	if (vars->transl == 1)
	{
		points->x += -1;
		points->y -= -1;
	}
	else if (vars->transl == 2)
	{
		points->x += 1;
		points->y -= 1;
	}
	else if (vars->transl == 3)
	{
		points->x += -1;
		points->y -= 1;
	}
	else if (vars->transl == 4)
	{
		points->x += 1;
		points->y -= -1;
	}
}
