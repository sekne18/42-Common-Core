/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:41:21 by jans              #+#    #+#             */
/*   Updated: 2025/02/13 14:18:13 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * PARAMETERS: context, values, mtl_ids
 * DESCRIPTION: Create an object from the line.
 * RETURNS: 1 if creation succeded, 0 if failed
 * */
int	build_sphere(t_context *context, char **values, t_list *mtl_ids, int index)
{
	t_material	*material;
	t_vec3		center;
	float		radius;

	material = get_material(values[3], context->scene->materials, mtl_ids);
	if (!material)
		return (0);
	center = get_vec3(values[1]);
	radius = ft_atof(values[2]);
	context->scene->objects[index] = create_sphere(center, radius);
	if (!context->scene->objects[index].type)
		return (0);
	context->scene->objects[index].material = material;
	return (1);
}

/*
 * PARAMETHERS: context, values, mtl_ids
 * DESCRIPTION: Create a plane from the line.
 * RETURNS: 1 if creation succeded, 0 if failed
 * */
int	build_plane(t_context *context, char **values, t_list *mtl_ids, int index)
{
	t_material	*material;
	t_vec3		point;
	t_vec3		normal;

	material = get_material(values[3], context->scene->materials, mtl_ids);
	if (!material)
		return (0);
	point = get_vec3(values[1]);
	normal = get_vec3(values[2]);
	normalize_local(&normal);
	context->scene->objects[index] = create_plane(normal, point);
	if (!context->scene->objects[index].type)
		return (0);
	context->scene->objects[index].material = material;
	return (1);
}

/*
 * PARAMETHERS: context, values, mtl_ids
 * DESCRIPTION: Create a plane from the line.
 * RETURNS: 1 if creation succeded, 0 if failed
 * */
int	build_quad(t_context *context, char **values, t_list *mtl_ids, int index)
{
	t_vec3		point;
	t_vec3		u;
	t_vec3		v;
	t_material	*material;

	material = get_material(values[4], context->scene->materials, mtl_ids);
	if (!material)
		return (0);
	point = get_vec3(values[1]);
	u = get_vec3(values[2]);
	v = get_vec3(values[3]);
	context->scene->objects[index] = create_quad(point, u, v);
	if (!context->scene->objects[index].type)
		return (0);
	context->scene->objects[index].material = material;
	return (1);
}

/*
 * PARAMETHERS: context, values, mtl_ids
 * DESCRIPTION: Create a cylinder from the line.
 * RETURNS: 1 if creation succeded, 0 if failed
 * */
int	build_cylinder(t_context *context, char **values, t_list *mtl_ids,
		int index)
{
	t_vec3		center;
	t_vec3		axis;
	float		radius;
	float		height;
	t_material	*material;

	material = get_material(values[5], context->scene->materials, mtl_ids);
	if (!material)
		return (0);
	center = get_vec3(values[1]);
	axis = get_vec3(values[2]);
	normalize_local(&axis);
	radius = ft_atof(values[3]);
	height = ft_atof(values[4]);
	context->scene->objects[index] = create_cylinder(center, axis, radius,
			height);
	if (!context->scene->objects[index].type)
		return (0);
	context->scene->objects[index].material = material;
	return (1);
}
