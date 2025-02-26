/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:22:04 by fmol              #+#    #+#             */
/*   Updated: 2025/02/18 16:39:38 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void	invert_normal(t_vec3 *normal, t_ray *ray)
{
	if (dot(normal, &ray->direction) > 0.0)
		mul_scalar_local(normal, -1);
}

t_vec3	*ray_at(t_vec3 *res, t_ray *ray, float t)
{
	mul_scalar(res, &ray->direction, t);
	add_local(res, &ray->origin);
	return (res);
}

float	check_hit(t_ray *ray, t_object *obj)
{
	float	t;

	t = -1.0;
	if (obj->type == SPHERE)
		t = hit_sphere(ray, obj->data);
	else if (obj->type == TRIANGLE)
		t = hit_triangle(ray, obj->data);
	else if (obj->type == PLANE)
		t = hit_plane(ray, obj->data);
	else if (obj->type == CYLINDER)
		t = hit_cylinder(ray, obj->data);
	else if (obj->type == QUAD)
		t = hit_quad(ray, obj->data);
	else if (obj->type == DISK)
		t = hit_disk(ray, obj->data);
	else if (obj->type == MESH)
		t = hit_bbox(ray, &obj->bbox);
	return (t);
}

float	hit_face(t_ray *ray, t_face *face, t_vec3 *vertices, t_vec3 *edges)
{
	t_vec3	tmp1;
	t_vec3	tmp2;
	float	det;
	float	u;
	float	v;

	cross(&tmp1, &ray->direction, edges + 1);
	det = dot(edges, &tmp1);
	if (det > -0.000001 && det < 0.000001)
		return (-1.0);
	det = 1.0 / det;
	sub(&tmp2, &ray->origin, &vertices[face->vertices[0]]);
	u = dot(&tmp2, &tmp1) * det;
	if (u < 0.0 || u > 1.0)
		return (-1.0);
	cross(&tmp1, &tmp2, edges);
	v = dot(&ray->direction, &tmp1) * det;
	if (v < 0.0 || u + v > 1.0)
		return (-1.0);
	u = dot(edges + 1, &tmp1) * det;
	if (u > 0.000001)
		return (u);
	return (-1.0);
}
