/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbox_union.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:02:37 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 16:06:13 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	grow_to_include_triangle(t_aabb *bbox, t_triangle *triangle)
{
	grow_to_include_point(bbox, &triangle->vertices[0]);
	grow_to_include_point(bbox, &triangle->vertices[1]);
	grow_to_include_point(bbox, &triangle->vertices[2]);
}

void	grow_to_include_sphere(t_aabb *bbox, t_sphere *sphere)
{
	t_vec3	vmin;
	t_vec3	vmax;

	sub(&vmin, &sphere->center, &(t_vec3){{sphere->radius,
		sphere->radius, sphere->radius}});
	add(&vmax, &sphere->center, &(t_vec3){{sphere->radius,
		sphere->radius, sphere->radius}});
	min_local(&bbox->min, &vmin);
	max_local(&bbox->max, &vmax);
}

void	grow_to_include_disk(t_aabb *bbox, t_disk *disk)
{
	t_vec3	vmin;
	t_vec3	vmax;
	t_vec3	tmp;

	tmp = (t_vec3){{disk->radius, disk->radius, disk->radius}};
	sub_scaled_local(&tmp, &disk->normal, dot(&tmp, &disk->normal));
	sub(&vmin, &disk->center, &tmp);
	add(&vmax, &disk->center, &tmp);
	add_scaled_local(&vmin, &disk->normal, -0.0001);
	add_scaled_local(&vmax, &disk->normal, 0.0001);
	min_local(&bbox->min, &vmin);
	max_local(&bbox->max, &vmax);
}

void	grow_to_include_quad(t_aabb *bbox, t_quad *quad)
{
	t_vec3	p2;

	add(&p2, &quad->point, &quad->u);
	add_local(&p2, &quad->v);
	add(&bbox->min, &quad->point, &quad->u);
	add(&bbox->max, &quad->point, &quad->v);
	min_local(&bbox->min, &p2);
	max_local(&bbox->max, &p2);
	min_local(&bbox->min, &quad->point);
	max_local(&bbox->max, &quad->point);
}

void	grow_to_include_cylinder(t_aabb *bbox, t_cylinder *cylinder)
{
	t_vec3	vmin;
	t_vec3	vmax;
	t_vec3	tmp;

	tmp = (t_vec3){{cylinder->radius, cylinder->radius, cylinder->radius}};
	sub_scaled_local(&tmp, &cylinder->axis, dot(&tmp, &cylinder->axis));
	sub(&vmin, &cylinder->center, &tmp);
	sub_scaled_local(&vmin, &cylinder->axis, cylinder->height * 0.5);
	tmp = (t_vec3){{cylinder->radius, cylinder->radius, cylinder->radius}};
	sub_scaled_local(&tmp, &cylinder->axis, dot(&tmp, &cylinder->axis));
	add(&vmax, &cylinder->center, &tmp);
	add_scaled_local(&vmax, &cylinder->axis, cylinder->height * 0.5);
	min_local(&bbox->min, &vmin);
	max_local(&bbox->max, &vmax);
}
