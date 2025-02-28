/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:18:46 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 15:13:15 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static inline float	hit_cylinder_caps(t_ray *ray, t_cylinder *cylinder, float t)
{
	t_vec3	base;
	t_vec3	normal;
	float	t2;

	base = cylinder->base;
	mul_scalar(&normal, &cylinder->axis, -1.0);
	t2 = hit_disk(ray, &(t_disk){base, cylinder->axis, cylinder->radius});
	if (t2 > 0.0 && (t2 < t || t < 0.0))
		t = t2;
	add_scaled_local(&base, &cylinder->axis, cylinder->height);
	t2 = hit_disk(ray, &(t_disk){base, cylinder->axis, cylinder->radius});
	if (t2 > 0.0 && (t2 < t || t < 0.0))
		t = t2;
	return (t);
}

static inline float	hit_cylinder_radius(t_ray *ray, t_cylinder *cylinder,
	t_vec3 *oc, t_vec3 *dir)
{
	t_vec3	tmp;
	float	d[3];
	float	b;
	float	t;

	tmp = *oc;
	sub_scaled_local(&tmp, &cylinder->axis, dot(&tmp, &cylinder->axis));
	d[2] = length_squared(dir);
	b = 2 * dot(dir, &tmp);
	d[0] = b * b - 4 * d[2]
		* (length_squared(&tmp) - cylinder->radius * cylinder->radius);
	if (d[0] < 0.0)
		return (-2.0);
	t = (-b - sqrt(d[0])) / (2 * d[2]);
	add_scaled(&tmp, oc, &ray->direction, t);
	d[1] = dot(&tmp, &cylinder->axis);
	if (t < 0.0 || d[1] < 0.0 || d[1] > cylinder->height)
	{
		t = (-b + sqrt(d[0])) / (2 * d[2]);
		add_scaled(&tmp, oc, &ray->direction, t);
		d[1] = dot(&tmp, &cylinder->axis);
		if (t < 0.0 || d[1] < 0.0 || d[1] > cylinder->height)
			t = -1.0;
	}
	return (t);
}

float	hit_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_vec3	oc;
	t_vec3	dir;
	float	t;

	sub(&oc, &ray->origin, &cylinder->base);
	dir = ray->direction;
	sub_scaled_local(&dir, &cylinder->axis,
		dot(&ray->direction, &cylinder->axis));
	t = hit_cylinder_radius(ray, cylinder, &oc, &dir);
	if (t < -1.5)
		return (-1.0);
	return (hit_cylinder_caps(ray, cylinder, t));
}
