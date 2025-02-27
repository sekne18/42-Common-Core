/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:35:47 by fmol              #+#    #+#             */
/*   Updated: 2025/02/12 10:21:24 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	*add_scalar(t_vec3 *dest, const t_vec3 *restrict a, float scalar)
{
	dest->x = a->x + scalar;
	dest->y = a->y + scalar;
	dest->z = a->z + scalar;
	return (dest);
}

t_vec3	*sub_scalar(t_vec3 *dest, const t_vec3 *restrict a, float scalar)
{
	dest->x = a->x - scalar;
	dest->y = a->y - scalar;
	dest->z = a->z - scalar;
	return (dest);
}

t_vec3	*mul_scalar(t_vec3 *dest, const t_vec3 *restrict a, float scalar)
{
	dest->x = a->x * scalar;
	dest->y = a->y * scalar;
	dest->z = a->z * scalar;
	return (dest);
}

t_vec3	*div_scalar(t_vec3 *dest, const t_vec3 *restrict a, float scalar)
{
	dest->x = a->x / scalar;
	dest->y = a->y / scalar;
	dest->z = a->z / scalar;
	return (dest);
}
