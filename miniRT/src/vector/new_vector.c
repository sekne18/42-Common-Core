/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:06:32 by fmol              #+#    #+#             */
/*   Updated: 2025/02/18 12:13:19 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	new_vector(float x, float y, float z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	*create_vector(float x, float y, float z)
{
	t_vec3	*new;

	new = malloc(sizeof(t_vec3));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	return (new);
}

t_vec3	*set_vector(t_vec3 *restrict dest, float x, float y, float z)
{
	dest->x = x;
	dest->y = y;
	dest->z = z;
	return (dest);
}

t_vec3	*copy_vector(t_vec3 *restrict dest, const t_vec3 *restrict src)
{
	dest->x = src->x;
	dest->y = src->y;
	dest->z = src->z;
	return (dest);
}

t_vec3	*add_copy(t_vec3 *restrict dest, const t_vec3 a)
{
	dest->x += a.x;
	dest->y += a.y;
	dest->z += a.z;
	return (dest);
}
