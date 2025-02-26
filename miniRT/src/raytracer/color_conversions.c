/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_conversions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:16:45 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 10:58:15 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

int	vec3_to_int(t_vec3 *color)
{
	return ((int)(fmin(fmax(color->x, 0.0), 1.0) * 255.999f) << 16
	| (int)(fmin(fmax(color->y, 0.0), 1.0) * 255.999f) << 8
	| (int)(fmin(fmax(color->z, 0.0), 1.0) * 255.999f));
}

t_vec3	int_to_vec3(int color)
{
	return ((t_vec3){{((color & 0xFF0000) >> 16) * INV_COLOR,
			((color & 0x00FF00) >> 8) * INV_COLOR,
			(color & 0x0000FF) * INV_COLOR}});
}

int	rgb_to_int(float r, float g, float b)
{
	return ((int)(r * 255.999f) << 16
		| (int)(g * 255.999f) << 8 | (int)(b * 255.999f));
}

void	int_to_rgb(int color, float *r, float *g, float *b)
{
	*r = (color & 0xFF0000) >> 16;
	*g = (color & 0x00FF00) >> 8;
	*b = (color & 0x0000FF);
}

int	rgb_mul(int color, float r, float g, float b)
{
	float		ir;
	float		ig;
	float		ib;

	int_to_rgb(color, &ir, &ig, &ib);
	ir *= r;
	ig *= g;
	ib *= b;
	return (rgb_to_int(ir, ig, ib));
}
