/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_ops_scaled2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:17:01 by jans              #+#    #+#             */
/*   Updated: 2025/02/18 13:31:04 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	*add_scaled_local(t_vec3 *a, const t_vec3 *restrict b, float scalar)
{
	a->x += b->x * scalar;
	a->y += b->y * scalar;
	a->z += b->z * scalar;
	return (a);
}

t_vec3	*add_scaled(t_vec3 *dest, const t_vec3 *restrict a,
		const t_vec3 *restrict b, float scalar)
{
	dest->x = a->x + b->x * scalar;
	dest->y = a->y + b->y * scalar;
	dest->z = a->z + b->z * scalar;
	return (dest);
}
