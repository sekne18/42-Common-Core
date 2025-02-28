/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:08:08 by fmol              #+#    #+#             */
/*   Updated: 2025/01/27 08:35:02 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	*add(t_vec3 *dest, const t_vec3 *restrict a, const t_vec3 *restrict b)
{
	dest->x = a->x + b->x;
	dest->y = a->y + b->y;
	dest->z = a->z + b->z;
	return (dest);
}

t_vec3	*sub(t_vec3 *dest, const t_vec3 *restrict a, const t_vec3 *restrict b)
{
	dest->x = a->x - b->x;
	dest->y = a->y - b->y;
	dest->z = a->z - b->z;
	return (dest);
}

t_vec3	*mul(t_vec3 *dest, const t_vec3 *restrict a, const t_vec3 *restrict b)
{
	dest->x = a->x * b->x;
	dest->y = a->y * b->y;
	dest->z = a->z * b->z;
	return (dest);
}

t_vec3	*div_vec(t_vec3 *dest, const t_vec3 *restrict a,
		const t_vec3 *restrict b)
{
	dest->x = a->x / b->x;
	dest->y = a->y / b->y;
	dest->z = a->z / b->z;
	return (dest);
}
