/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jitter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:24:11 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 11:00:03 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void	jitter_ray(t_ray *ray, t_camera *c, unsigned int *seed)
{
	t_vec2	jitter;

	jitter = random_circle_vec(seed);
	add_scaled_local(&ray->origin, &c->viewport->u, jitter.x * JITTER);
	add_scaled_local(&ray->origin, &c->viewport->v, jitter.y * JITTER);
}

t_vec3	jitter_point(t_vec3 point, unsigned int *seed, t_camera *c)
{
	t_vec2	jitter;

	jitter = random_circle_vec(seed);
	add_scaled_local(&point, &c->viewport->u, jitter.x * JITTER_FOCUS);
	add_scaled_local(&point, &c->viewport->v, jitter.y * JITTER_FOCUS);
	return (point);
}

t_vec3	calc_ray_dir(t_vec3 origin, t_vec3 viewpoint)
{
	t_vec3	dir;

	sub(&dir, &viewpoint, &origin);
	normalize_local(&dir);
	return (dir);
}

t_vec3	get_viewpoint(t_camera *c, int x, int y)
{
	t_vec3	tmp;

	tmp = c->viewport->upper_left_corner;
	add_scaled_local(&tmp, &c->viewport->u, c->viewport->delta_u * x);
	add_scaled_local(&tmp, &c->viewport->v, c->viewport->delta_v * y);
	return (tmp);
}
