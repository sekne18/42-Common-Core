/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:25:14 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 15:29:59 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

//for jittering / blurring
// will both jitter the origin before (blur)
// and after (anti-aliasing) calculating the ray direction
void	calc_jittered_ray(t_ray *ray, t_camera *c,
	t_vec2 coords, unsigned int *seed)
{
	ray->origin = jitter_point(c->origin, seed, c);
	ray->direction = calc_ray_dir(ray->origin,
			get_viewpoint(c, coords.x, coords.y));
	jitter_ray(ray, c, seed);
	ray->invdir = (t_vec3){{1.0 / ray->direction.x,
		1.0 / ray->direction.y, 1.0 / ray->direction.z}};
}

void	calc_ray(t_ray *ray, t_camera *c, int x, int y)
{
	t_vec3	tmp;

	tmp = c->viewport->upper_left_corner;
	add_scaled_local(&tmp, &c->viewport->u, c->viewport->delta_u * x);
	add_scaled_local(&tmp, &c->viewport->v, c->viewport->delta_v * y);
	sub_local(&tmp, &c->origin);
	normalize_local(&tmp);
	ray->origin = c->origin;
	ray->direction = tmp;
	ray->invdir = (t_vec3){{1.0 / ray->direction.x,
		1.0 / ray->direction.y, 1.0 / ray->direction.z}};
}
