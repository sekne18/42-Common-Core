/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbox_primitives.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:01:16 by fmol              #+#    #+#             */
/*   Updated: 2025/02/18 11:45:34 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_aabb	get_triangle_aabb(t_triangle *triangle)
{
	t_aabb	bbox;

	bbox.min = (t_vec3){{INFINITY, INFINITY, INFINITY}};
	bbox.max = (t_vec3){{-INFINITY, -INFINITY, -INFINITY}};
	grow_to_include_point(&bbox, &triangle->vertices[0]);
	grow_to_include_point(&bbox, &triangle->vertices[1]);
	grow_to_include_point(&bbox, &triangle->vertices[2]);
	pad(&bbox, BBOX_PADDING);
	return (bbox);
}

t_aabb	get_sphere_aabb(t_sphere *sphere)
{
	t_aabb	bbox;

	bbox.min = sphere->center;
	bbox.max = sphere->center;
	sub(&bbox.min, &bbox.min, &(t_vec3){{sphere->radius,
		sphere->radius, sphere->radius}});
	add(&bbox.max, &bbox.max, &(t_vec3){{sphere->radius,
		sphere->radius, sphere->radius}});
	pad(&bbox, BBOX_PADDING);
	return (bbox);
}

t_aabb	get_cylinder_aabb(t_cylinder *cylinder)
{
	t_aabb	bbox;
	t_vec3	vmin;
	t_vec3	vmax;
	t_vec3	tmp;
	t_vec3	tmp2;

	sub_scaled(&vmin, &cylinder->center, &cylinder->axis,
		cylinder->height * 0.5);
	add_scaled(&vmax, &cylinder->center, &cylinder->axis,
		cylinder->height * 0.5);
	min(&bbox.min, &vmin, &vmax);
	max(&bbox.max, &vmin, &vmax);
	tmp = (t_vec3){{1, 1, 1}};
	copy_vector(&tmp2, &cylinder->axis);
	mul_local(&tmp2, &cylinder->axis);
	sub_local(&tmp, &tmp2);
	set_vector(&tmp2, sqrtf(tmp.x), sqrtf(tmp.y), sqrtf(tmp.z));
	sub_scaled_local(&bbox.min, &tmp2, cylinder->radius);
	add_scaled_local(&bbox.max, &tmp2, cylinder->radius);
	pad(&bbox, BBOX_PADDING);
	return (bbox);
}

t_aabb	get_quad_aabb(t_quad *quad)
{
	t_aabb	bbox;
	t_vec3	p2;

	add(&p2, &quad->point, &quad->u);
	add_local(&p2, &quad->v);
	add(&bbox.min, &quad->point, &quad->u);
	add(&bbox.max, &quad->point, &quad->v);
	min_local(&bbox.min, &p2);
	max_local(&bbox.max, &p2);
	min_local(&bbox.min, &quad->point);
	max_local(&bbox.max, &quad->point);
	pad(&bbox, BBOX_PADDING);
	return (bbox);
}

t_aabb	get_disk_aabb(t_disk *disk)
{
	t_aabb	bbox;
	t_vec3	vmin;
	t_vec3	vmax;
	t_vec3	tmp;

	tmp = (t_vec3){{disk->radius, disk->radius, disk->radius}};
	sub_scaled_local(&tmp, &disk->normal, dot(&tmp, &disk->normal));
	sub(&vmin, &disk->center, &tmp);
	add(&vmax, &disk->center, &tmp);
	add_scaled_local(&vmin, &disk->normal, -0.0001);
	add_scaled_local(&vmax, &disk->normal, 0.0001);
	bbox.min = vmin;
	bbox.max = vmax;
	pad(&bbox, BBOX_PADDING);
	return (bbox);
}
