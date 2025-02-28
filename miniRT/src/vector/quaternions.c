/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:39:11 by fmol              #+#    #+#             */
/*   Updated: 2025/02/12 10:20:55 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_quat	*normalize_quat(t_quat *q)
{
	float	magnitude;

	magnitude = sqrtf(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
	q->x = q->x / magnitude;
	q->y = q->y / magnitude;
	q->z = q->z / magnitude;
	q->w = q->w / magnitude;
	return (q);
}

t_quat	quat_from_axis_angle(const t_vec3 *restrict axis, float angle)
{
	t_quat	result;
	float	sin_a;

	sin_a = sinf(angle / 2);
	result.x = axis->x * sin_a;
	result.y = axis->y * sin_a;
	result.z = axis->z * sin_a;
	result.w = cosf(angle / 2);
	normalize_quat(&result);
	return (result);
}

t_quat	mul_quat(const t_quat *restrict a, const t_quat *restrict b)
{
	t_quat	result;

	result.x = a->w * b->x + a->x * b->w + a->y * b->z - a->z * b->y;
	result.y = a->w * b->y - a->x * b->z + a->y * b->w + a->z * b->x;
	result.z = a->w * b->z + a->x * b->y - a->y * b->x + a->z * b->w;
	result.w = a->w * b->w - a->x * b->x - a->y * b->y - a->z * b->z;
	return (result);
}

t_vec3	rotate_vec(const t_vec3 *restrict v, const t_quat *restrict q)
{
	t_quat	vq;
	t_quat	q_inv;
	t_quat	result;
	t_quat	tmp;

	vq.x = v->x;
	vq.y = v->y;
	vq.z = v->z;
	vq.w = 0;
	q_inv.x = -q->x;
	q_inv.y = -q->y;
	q_inv.z = -q->z;
	q_inv.w = q->w;
	tmp = mul_quat(q, &vq);
	result = mul_quat(&tmp, &q_inv);
	return ((t_vec3){{result.x, result.y, result.z}});
}
