/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:02:31 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 11:01:20 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

float	random_float(unsigned int *seed)
{
	unsigned int	r;

	*seed = *seed * 747796405 + 2891336453;
	r = ((*seed >> ((*seed >> 28) + 4)) ^ *seed) * 277803737;
	r = (r >> 22) ^ r;
	return (r / 4294967295.0);
}

t_vec3	random_unit_vec(unsigned int *seed)
{
	t_vec3	p;
	float	phi;
	float	theta;

	phi = 2 * M_PI * random_float(seed);
	theta = acosf(1.0f - 2.0f * random_float(seed));
	p = (t_vec3){{
		sinf(theta) * cosf(phi),
		sinf(theta) * sinf(phi),
		cosf(theta)
	}};
	return (p);
}

t_vec3	random_hemisphere_vec(const t_vec3 *restrict normal, unsigned int *seed)
{
	t_vec3	in_unit_sphere;
	t_vec3	p;

	in_unit_sphere = random_unit_vec(seed);
	if (dot(&in_unit_sphere, normal) > 0.0)
		p = in_unit_sphere;
	else
		mul_scalar(&p, &in_unit_sphere, -1.0);
	return (p);
}

t_vec2	random_circle_vec(unsigned int *seed)
{
	float	r;
	float	theta;

	r = sqrtf(random_float(seed));
	theta = 2 * M_PI * random_float(seed);
	return ((t_vec2){r * cosf(theta), r * sinf(theta)});
}
