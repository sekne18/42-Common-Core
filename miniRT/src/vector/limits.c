/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:16:19 by fmol              #+#    #+#             */
/*   Updated: 2025/02/12 10:19:36 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	min(t_vec3 *dest, const t_vec3 *restrict a, const t_vec3 *restrict b)
{
	if (a->x < b->x)
		dest->x = a->x;
	else
		dest->x = b->x;
	if (a->y < b->y)
		dest->y = a->y;
	else
		dest->y = b->y;
	if (a->z < b->z)
		dest->z = a->z;
	else
		dest->z = b->z;
}

void	max(t_vec3 *dest, const t_vec3 *restrict a, const t_vec3 *restrict b)
{
	if (a->x > b->x)
		dest->x = a->x;
	else
		dest->x = b->x;
	if (a->y > b->y)
		dest->y = a->y;
	else
		dest->y = b->y;
	if (a->z > b->z)
		dest->z = a->z;
	else
		dest->z = b->z;
}

void	min_local(t_vec3 *a, const t_vec3 *b)
{
	if (a->x > b->x)
		a->x = b->x;
	if (a->y > b->y)
		a->y = b->y;
	if (a->z > b->z)
		a->z = b->z;
}

void	max_local(t_vec3 *a, const t_vec3 *b)
{
	if (a->x < b->x)
		a->x = b->x;
	if (a->y < b->y)
		a->y = b->y;
	if (a->z < b->z)
		a->z = b->z;
}
