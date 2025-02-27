/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:54:47 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 10:57:58 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

int	rgb_add(int color, float r, float g, float b)
{
	float		ir;
	float		ig;
	float		ib;

	int_to_rgb(color, &ir, &ig, &ib);
	ir += r;
	ig += g;
	ib += b;
	return (rgb_to_int(ir, ig, ib));
}

int	color_add(int color, int add)
{
	float		r;
	float		g;
	float		b;

	int_to_rgb(add, &r, &g, &b);
	rgb_add(color, r, g, b);
	return (color);
}

int	color_mul(int color, int mul)
{
	float		r;
	float		g;
	float		b;

	int_to_rgb(mul, &r, &g, &b);
	rgb_mul(color, r, g, b);
	return (color);
}

int	color_scale(int color, float scale)
{
	float		r;
	float		g;
	float		b;

	int_to_rgb(color, &r, &g, &b);
	r *= scale;
	g *= scale;
	b *= scale;
	return (rgb_to_int(r, g, b));
}
