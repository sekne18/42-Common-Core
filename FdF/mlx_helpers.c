/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:38:31 by jans              #+#    #+#             */
/*   Updated: 2024/11/01 16:42:57 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	projected_x(t_point *p, int scale)
{
	float	rotation;

	rotation = ((M_PI * 30) / 180);
	return (((p->x * scale) - (p->y * scale)) * cos(rotation));
}

int	projected_y(t_point *p, int scale)
{
	float	rotation;

	rotation = ((M_PI * 30) / 180);
	return (((p->x * scale) + (p->y * scale)) * sin(rotation) - (p->z * scale));
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
