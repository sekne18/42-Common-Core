/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:38:31 by jans              #+#    #+#             */
/*   Updated: 2024/10/25 15:22:24 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));	
	*(unsigned int *)dst = color;
}

int	mouse_hook(int keycode, t_vars *vars)
{
	keycode++;
	vars++;
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 27)
		mlx_destroy_display(vars->mlx);
	return (0);
}

int	projected_x(t_point *p)
{
	float	rotation;

	rotation = ((M_PI * 30) / 180);
	return (((p->x - p->y) * cos(rotation)) * 2);
}

int	projected_y(t_point *p)
{
	float	rotation;

	rotation = ((M_PI * 30) / 180);
	return (((p->x + p->y) * sin(rotation) - p->z) * 2);
}