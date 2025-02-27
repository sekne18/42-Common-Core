/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_record_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:21:17 by fmol              #+#    #+#             */
/*   Updated: 2025/02/18 16:46:27 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void	fill_face_record(t_hit_record *record, t_ray *ray, float t)
{
	record->hit = 1;
	record->t = t;
	ray_at(&record->point, ray, t);
	record->type = MESH;
}

void	set_face_normal(t_hit_record *record, t_mesh *mesh,
	unsigned int *indices)
{
	record->normal = mesh->normals[indices[0]];
}

void	fill_triangle_record(t_hit_record *record, t_ray *ray,
	t_object *obj, float t)
{
	t_triangle	*triangle;

	triangle = obj->data;
	record->t = t;
	ray_at(&record->point, ray, t);
	record->normal = triangle->normal;
	invert_normal(&record->normal, ray);
	record->type = TRIANGLE;
}

void	fill_cylinder_record(t_hit_record *record, t_ray *ray,
	t_object *obj, float t)
{
	t_cylinder	*cylinder;
	t_vec3		oc;
	float		height;

	cylinder = obj->data;
	record->t = t;
	record->type = CYLINDER;
	ray_at(&record->point, ray, t);
	sub(&oc, &record->point, &cylinder->base);
	height = dot(&oc, &cylinder->axis);
	if ((height < 0.000001 && height > -0.000001)
		|| (height > cylinder->height - 0.000001
			&& height < cylinder->height + 0.000001))
	{
		record->normal = cylinder->axis;
		invert_normal(&record->normal, ray);
		return ;
	}
	add_scaled(&oc, &cylinder->base, &cylinder->axis, height);
	normalize_local(sub(&record->normal, &record->point, &oc));
	invert_normal(&record->normal, ray);
}
