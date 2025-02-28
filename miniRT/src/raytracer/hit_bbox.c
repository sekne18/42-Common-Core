/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bbox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:40:30 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 09:44:13 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static inline void	set_limits(float *tmin, float *tmax, float t0, float t1)
{
	if (t0 < t1)
	{
		*tmin = fmaxf(*tmin, t0);
		*tmax = fminf(*tmax, t1);
	}
	else
	{
		*tmin = fmaxf(*tmin, t1);
		*tmax = fminf(*tmax, t0);
	}
}

float	hit_bbox(t_ray *ray, t_aabb *box)
{
	float	t0;
	float	t1;
	float	tmin;
	float	tmax;	
	int		i;

	tmin = -INFINITY;
	tmax = INFINITY;
	i = -1;
	while (++i < 3)
	{
		t0 = (box->min.v[i] - ray->origin.v[i]) * ray->invdir.v[i];
		t1 = (box->max.v[i] - ray->origin.v[i]) * ray->invdir.v[i];
		set_limits(&tmin, &tmax, t0, t1);
		if (tmax < tmin)
			return (INFINITY);
	}
	if (tmin < 0.0f && tmax >= 0.0f)
		return (tmax);
	else if (tmin < 0.0f)
		return (INFINITY);
	return (tmin);
}
