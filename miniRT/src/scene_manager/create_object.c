/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:59:58 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 16:39:22 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_object	create_sphere(t_vec3 center, float radius)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return ((t_object){0});
	ft_memcpy(sphere, &(t_sphere){center, radius}, sizeof(t_sphere));
	return ((t_object){NULL, SPHERE, get_sphere_aabb(sphere), center, sphere});
}

t_object	create_plane(t_vec3 normal, t_vec3 point)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return ((t_object){0});
	ft_memcpy(plane, &(t_plane){normal, point}, sizeof(t_plane));
	return ((t_object){NULL, PLANE, get_plane_aabb(plane), point, plane});
}

t_object	create_cylinder(t_vec3 center, t_vec3 axis,
	float radius, float height)
{
	t_cylinder	*cylinder;
	t_vec3		base;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return ((t_object){0});
	base = center;
	sub_scaled_local(&base, &axis, height * 0.5f);
	ft_memcpy(cylinder, &(t_cylinder){center, base,
		axis, radius, height}, sizeof(t_cylinder));
	return ((t_object){NULL, CYLINDER,
		get_cylinder_aabb(cylinder), center, cylinder});
}

t_object	create_quad(t_vec3 point, t_vec3 u, t_vec3 v)
{
	t_quad	*quad;
	t_vec3	normal;
	t_vec3	w;
	t_vec3	center;

	quad = malloc(sizeof(t_quad));
	if (!quad)
		return ((t_object){0});
	cross(&normal, &u, &v);
	normalize_local(&normal);
	w = normal;
	mul_scalar_local(&w, 1 / (length(&u) * length(&v)
			* dot(&normal, &normal)));
	add_scaled(&center, &point, &u, 0.5);
	add_scaled_local(&center, &v, 0.5);
	ft_memcpy(quad, &(t_quad){point, u, v, normal, w}, sizeof(t_quad));
	return ((t_object){NULL, QUAD, get_quad_aabb(quad), center, quad});
}

t_object	create_disk(t_vec3 center, t_vec3 normal, float radius)
{
	t_disk	*disk;

	disk = malloc(sizeof(t_disk));
	if (!disk)
		return ((t_object){0});
	ft_memcpy(disk, &(t_disk){center, normal, radius}, sizeof(t_disk));
	return ((t_object){NULL, DISK, get_disk_aabb(disk), center, disk});
}
