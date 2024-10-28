/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:10:02 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/28 19:05:03 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned int	interpolate_color(int min_z, int max_z, int z)
{
	t_color	color_low;
	t_color	color_high;
	float	z_ratio;
	t_color	color;

	color_low.r = 0;
	color_low.g = 232;
	color_low.b = 0;
	color_high.r = 252;
	color_high.g = 109;
	color_high.b = 0;
	z_ratio = (float)(z - min_z) / (max_z - min_z);
	if (z_ratio < 0)
		z_ratio = 0;
	if (z_ratio > 1)
		z_ratio = 1;
	color.r = color_low.r + (color_high.r - color_low.r) * z_ratio;
	color.g = color_low.g + (color_high.g - color_low.g) * z_ratio;
	color.b = color_low.b + (color_high.b - color_low.b) * z_ratio;
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	free_points(t_point ***points)
{
	int	x;
	int	y;
	int	rows;
	int	cols;

	cols = points[0][0]->info->cols;
	rows = points[0][0]->info->rows;
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			free(points[y][x]->info);
			free(points[y][x]);
			x++;
		}
		free(points[y]);
		y++;
	}
	free(points);
}

void	check_if_square(t_point ***points, char **map, t_vars *vars)
{
	if (points[0][0]->info->rows == points[0][0]->info->cols)
	{
		free_all(map);
		free_points(points);
		ft_close_win(vars);
	}
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
			free_points(vars->points);
		free(vars);
	}
}
