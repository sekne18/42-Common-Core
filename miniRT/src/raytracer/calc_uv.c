/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_uv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:19:04 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 10:37:06 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void	set_sphere_uv(t_hit_record *record)
{
	record->uv.x = 1.0 - (atan2f(-record->normal.z, record->normal.x)
			/ (2 * M_PI) + 0.5);
	record->uv.y = 1.0 - acosf(-record->normal.y) / M_PI;
}

void	set_uv(t_hit_record *record)
{
	if (record->type == SPHERE)
		set_sphere_uv(record);
}
