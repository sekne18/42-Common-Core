/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbox_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:59:56 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 16:07:56 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	pad(t_aabb *box, float padding)
{
	sub_scalar_local(&box->min, padding);
	add_scalar_local(&box->max, padding);
}

void	pad_direction(t_aabb *box, t_vec3 *direction, float padding)
{
	t_vec3	tmp;

	mul_scalar(&tmp, direction, padding);
	sub_local(&box->min, &tmp);
	add_local(&box->max, &tmp);
}

void	grow_to_include_point(t_aabb *bbox, t_vec3 *point)
{
	min_local(&bbox->min, point);
	max_local(&bbox->max, point);
}

int	contains_bbox(t_aabb *bbox, t_aabb *to_test)
{
	if (to_test->min.x < bbox->min.x || to_test->min.y < bbox->min.y
		|| to_test->min.z < bbox->min.z)
		return (0);
	if (to_test->max.x > bbox->max.x || to_test->max.y > bbox->max.y
		|| to_test->max.z > bbox->max.z)
		return (0);
	return (1);
}

float	surface_area(t_aabb *bbox)
{
	t_vec3	tmp;

	sub(&tmp, &bbox->max, &bbox->min);
	return (2 * (tmp.x * tmp.y + tmp.x * tmp.z + tmp.y * tmp.z));
}
