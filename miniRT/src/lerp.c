/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:51:02 by fmol              #+#    #+#             */
/*   Updated: 2025/02/12 13:16:12 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lerp.h"

t_vec3	lerp_vec(const t_vec3 *a, const t_vec3 *b, float t)
{
	t_vec3	result;

	result.x = a->x + t * (b->x - a->x);
	result.y = a->y + t * (b->y - a->y);
	result.z = a->z + t * (b->z - a->z);
	return (result);
}

float	lerp_float(float a, float b, float t)
{
	return (a + t * (b - a));
}

t_vec3	lerp_vec_multiple(const t_vec3 *list, size_t size, float t)
{
	float	delta;
	size_t	i;

	delta = 1.0 / (size - 1);
	i = (size_t)(t / delta);
	if (i == size - 1)
		return (list[size - 1]);
	return (lerp_vec(&list[i], &list[i + 1], (t - i * delta) / delta));
}
