/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:46:52 by fmol              #+#    #+#             */
/*   Updated: 2025/02/12 10:19:46 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	*normalize(t_vec3 *dest, const t_vec3 *restrict a)
{
	float	len;

	len = length(a);
	dest->x = a->x / len;
	dest->y = a->y / len;
	dest->z = a->z / len;
	return (dest);
}

/* more optimal?
len = 1 / len;
a->x *= len;
a->y *= len;
a->z *= len;
*/
t_vec3	*normalize_local(t_vec3 *a)
{
	float	len;

	len = length(a);
	a->x /= len;
	a->y /= len;
	a->z /= len;
	return (a);
}
