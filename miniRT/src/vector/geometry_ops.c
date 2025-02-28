/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:45:20 by fmol              #+#    #+#             */
/*   Updated: 2025/02/13 09:22:05 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	*cross(t_vec3 *dest, const t_vec3 *restrict a, const t_vec3 *restrict b)
{
	dest->x = a->y * b->z - a->z * b->y;
	dest->y = a->z * b->x - a->x * b->z;
	dest->z = a->x * b->y - a->y * b->x;
	return (dest);
}

t_vec3	*cross_local(t_vec3 *a, const t_vec3 *restrict b)
{
	t_vec3	tmp;

	tmp.x = a->y * b->z - a->z * b->y;
	tmp.y = a->z * b->x - a->x * b->z;
	tmp.z = a->x * b->y - a->y * b->x;
	a->x = tmp.x;
	a->y = tmp.y;
	a->z = tmp.z;
	return (a);
}

float	dot(const t_vec3 *restrict a, const t_vec3 *restrict b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

float	length(const t_vec3 *restrict a)
{
	return (sqrtf(a->x * a->x + a->y * a->y + a->z * a->z));
}

float	length_squared(const t_vec3 *restrict a)
{
	return (a->x * a->x + a->y * a->y + a->z * a->z);
}
