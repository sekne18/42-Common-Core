/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_record.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:15:07 by fmol              #+#    #+#             */
/*   Updated: 2025/02/19 08:52:36 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void	fill_sphere_record(t_hit_record *record, t_ray *ray,
	t_object *obj, float t)
{
	t_sphere	*sphere;

	sphere = obj->data;
	record->t = t;
	ray_at(&record->point, ray, t);
	sub(&record->normal, &record->point, &sphere->center);
	div_scalar_local(&record->normal, sphere->radius);
	invert_normal(&record->normal, ray);
	record->type = SPHERE;
}

void	fill_plane_record(t_hit_record *record, t_ray *ray,
	t_object *obj, float t)
{
	t_plane	*plane;

	plane = obj->data;
	record->t = t;
	ray_at(&record->point, ray, t);
	record->normal = plane->normal;
	invert_normal(&record->normal, ray);
	record->type = PLANE;
}

void	fill_quad_record(t_hit_record *record, t_ray *ray,
	t_object *obj, float t)
{
	t_quad	*quad;

	quad = obj->data;
	record->t = t;
	ray_at(&record->point, ray, t);
	record->normal = quad->normal;
	invert_normal(&record->normal, ray);
	record->type = QUAD;
}

void	fill_disk_record(t_hit_record *record, t_ray *ray,
	t_object *obj, float t)
{
	t_disk	*disk;

	disk = obj->data;
	record->t = t;
	ray_at(&record->point, ray, t);
	record->normal = disk->normal;
	invert_normal(&record->normal, ray);
	record->type = DISK;
}

void	fill_record(t_hit_record *record, t_ray *ray, t_object *object, float t)
{
	record->material = object->material;
	record->normal = (t_vec3){{0, 0, 0}};
	record->hit = 1;
	if (object->type == SPHERE)
		fill_sphere_record(record, ray, object, t);
	else if (object->type == TRIANGLE)
		fill_triangle_record(record, ray, object, t);
	else if (object->type == PLANE)
		fill_plane_record(record, ray, object, t);
	else if (object->type == CYLINDER)
		fill_cylinder_record(record, ray, object, t);
	else if (object->type == QUAD)
		fill_quad_record(record, ray, object, t);
	else if (object->type == DISK)
		fill_disk_record(record, ray, object, t);
	else
	{
		record->hit = 0;
		return ;
	}
	set_uv(record);
}
