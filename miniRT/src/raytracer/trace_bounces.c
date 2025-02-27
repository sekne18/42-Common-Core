/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_bounces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:21:58 by fmol              #+#    #+#             */
/*   Updated: 2025/02/18 14:44:52 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void	reflect(t_vec3 *dest, const t_vec3 *incident, const t_vec3 *normal)
{
	t_vec3	tmp;

	mul_scalar(&tmp, normal, 2 * dot(incident, normal));
	sub(dest, incident, &tmp);
}

// ri should be '1/refractive_index' when light enters
// the object and 'refractive_index' when it leaves the object
float	refract(t_vec3 *dest, const t_vec3 *incident, const t_vec3 *normal,
	float refractive_index)
{
	float	cos_theta;
	float	sin_theta;
	float	ri;

	set_vector(dest, 0.0, 0.0, 0.0);
	cos_theta = fminf(dot(incident, normal), 1.0);
	sin_theta = sqrtf(1.0 - cos_theta * cos_theta);
	if (dot(incident, normal) < 0.0)
		ri = refractive_index;
	else
		ri = 1.0 / refractive_index;
	if (ri * sin_theta > 1.0)
		return (-1.0);
	add_scaled(dest, incident, normal, cos_theta);
	mul_scalar_local(dest, refractive_index);
	add_scaled_local(dest, normal, -sqrtf(fabs(1.0 - length_squared(dest))));
	return (1.0);
}

static inline void	set_modifiers(float *smoothness,
	float *refraction_bounce, const t_hit_record *record, unsigned int *seed)
{
	if (*refraction_bounce < 0.0)
		*smoothness = 1.0;
	else if (record->material->specular_intensity < random_float(seed))
		*smoothness = 0.0;
	if (*refraction_bounce > 0.5
		&& record->material->refraction_intensity >= random_float(seed))
		*refraction_bounce = 1.0;
	else
		*refraction_bounce = 0.0;
}

//TODO: clean this mess up (+ use schlick's approximation for
// reflection that varies with angle for refractive objects)
float	set_bounce_ray_dir(t_ray *ray, const t_hit_record *record,
	unsigned int *seed)
{
	t_vec3	diffuse;
	t_vec3	specular;
	t_vec3	refraction;
	float	refraction_bounce;
	float	smoothness;

	set_vector(&specular, 0.0, 0.0, 0.0);
	smoothness = record->material->smoothness;
	diffuse = random_hemisphere_vec(&record->normal, seed);
	add_local(&diffuse, &record->normal);
	normalize_local(&diffuse);
	refraction_bounce = 0.0;
	if (record->material->refraction_intensity > 0.0)
		refraction_bounce = refract(&refraction, &ray->direction,
				&record->normal, record->material->refractive_index);
	if (record->material->specular_intensity > 0.0)
		reflect(&specular, &ray->direction, &record->normal);
	set_modifiers(&smoothness, &refraction_bounce, record, seed);
	ray->direction = lerp_vec(&diffuse, &specular, smoothness);
	ray->direction = lerp_vec(&ray->direction, &refraction, refraction_bounce);
	normalize_local(&ray->direction);
	set_vector(&ray->invdir, 1.0 / ray->direction.x, 1.0 / ray->direction.y,
		1.0 / ray->direction.z);
	return (smoothness);
}
