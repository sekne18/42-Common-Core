/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:05:30 by jsekne            #+#    #+#             */
/*   Updated: 2024/11/26 11:06:40 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_point_array(t_point **point_arr, int size)
{
	int	i;

	if (!point_arr)
		return ;
	i = 0;
	while (i < size)
	{
		if (point_arr[i])
			free(point_arr[i]);
		i++;
	}
	free(point_arr);
}

void	free_points(t_point ***points, t_vars *vars)
{
	int	x;
	int	y;
	int	rows;
	int	cols;

	cols = vars->info->cols;
	rows = vars->info->rows;
	y = -1;
	while (++y < rows)
	{
		x = -1;
		while (++x < cols)
			free(points[y][x]);
		if (*points)
			free(points[y]);
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
		if (vars->info)
			free(vars->info);
		free(vars);
	}
}
