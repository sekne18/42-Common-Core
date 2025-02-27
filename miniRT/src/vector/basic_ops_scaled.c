/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_ops_scaled.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:45:31 by fmol              #+#    #+#             */
/*   Updated: 2025/02/12 10:19:01 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	*sub_scaled_local(t_vec3 *a, const t_vec3 *restrict b, float scalar)
{
	a->x -= b->x * scalar;
	a->y -= b->y * scalar;
	a->z -= b->z * scalar;
	return (a);
}

t_vec3	*sub_scaled(t_vec3 *dest, const t_vec3 *restrict a,
		const t_vec3 *restrict b, float scalar)
{
	dest->x = a->x - b->x * scalar;
	dest->y = a->y - b->y * scalar;
	dest->z = a->z - b->z * scalar;
	return (dest);
}

t_vec3	*sub_scaled_vec(t_vec3 *dest, const t_vec3 *restrict a,
		const t_vec3 *restrict b, const t_vec3 *restrict scalar)
{
	dest->x = a->x - b->x * scalar->x;
	dest->y = a->y - b->y * scalar->y;
	dest->z = a->z - b->z * scalar->z;
	return (dest);
}

t_vec3	*mul_scaled_local(t_vec3 *a, const t_vec3 *restrict b, float scalar)
{
	a->x *= b->x * scalar;
	a->y *= b->y * scalar;
	a->z *= b->z * scalar;
	return (a);
}

t_vec3	*div_scaled_local(t_vec3 *a, const t_vec3 *restrict b, float scalar)
{
	a->x /= b->x * scalar;
	a->y /= b->y * scalar;
	a->z /= b->z * scalar;
	return (a);
}
