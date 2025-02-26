/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_objects2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:05:19 by jans              #+#    #+#             */
/*   Updated: 2025/02/13 14:03:10 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	build_specific_object(t_context *context, char **split,
		t_list *mtl_ids, t_obj_count *count)
{
	int	status;
	int	type;

	status = 0;
	type = determine_object_type(split[0]);
	if (type == SPHERE)
		status = build_sphere(context, split, mtl_ids, calc_obj_i(count));
	else if (type == QUAD)
		status = build_quad(context, split, mtl_ids, calc_obj_i(count));
	else if (type == CYLINDER)
		status = build_cylinder(context, split, mtl_ids, calc_obj_i(count));
	else if (type == TRIANGLE)
		status = build_triangle(context, split, mtl_ids, calc_obj_i(count));
	else if (type == DISK)
		status = build_disk(context, split, mtl_ids, calc_obj_i(count));
	else if (type == PLANE)
		status = build_plane(context, split, mtl_ids, calc_plane_i(count));
	else if (type == MESH)
		status = build_mesh(context, split, mtl_ids, count->mesh_i);
	return (status);
}

/*
 * PARAMETERS: context, line
 * DESCRIPTION: Creates objects from the line.
 * RETURNS: 1 if the values are valid, 0 if the values are invalid.
 * */
int	build_objects(t_context *context, char *line, t_list *mtl_ids,
		t_obj_count *count)
{
	char	**split;
	int		status;
	int		type;

	split = ft_split(line, ' ');
	if (!split)
		return (ERR_MEM);
	type = determine_object_type(split[0]);
	status = build_specific_object(context, split, mtl_ids, count);
	if (status && type == MESH)
		count->mesh_i++;
	else if (status && type == PLANE)
		count->plane_i++;
	else if (status)
		count->obj_i++;
	return (ft_free_split(split), status);
}

/*
 * PARAMETHERS: context, values, mtl_ids
 * DESCRIPTION: Create a trangle from the line.
 * RETURNS: 1 if creation succeded, 0 if failed
 * */
int	build_triangle(t_context *context, char **values, t_list *mtl_ids,
		int index)
{
	t_vec3		vertices[3];
	t_material	*material;

	material = get_material(values[4], context->scene->materials, mtl_ids);
	if (!material)
		return (0);
	vertices[0] = get_vec3(values[1]);
	vertices[1] = get_vec3(values[2]);
	vertices[2] = get_vec3(values[3]);
	context->scene->objects[index] = create_triangle(vertices);
	if (!context->scene->objects[index].type)
		return (0);
	context->scene->objects[index].material = material;
	return (1);
}

/*
 * PARAMETHERS: context, values, mtl_ids
 * DESCRIPTION: Create a disk from the line.
 * RETURNS: 1 if creation succeded, 0 if failed
 * */
int	build_disk(t_context *context, char **values, t_list *mtl_ids, int index)
{
	t_vec3		center;
	t_vec3		normal;
	float		radius;
	t_material	*material;

	material = get_material(values[4], context->scene->materials, mtl_ids);
	if (!material)
		return (0);
	center = get_vec3(values[1]);
	normal = get_vec3(values[2]);
	normalize_local(&normal);
	radius = ft_atof(values[3]);
	context->scene->objects[index] = create_disk(center, normal, radius);
	if (!context->scene->objects[index].type)
		return (0);
	context->scene->objects[index].material = material;
	return (1);
}

int	build_mesh(t_context *context, char **values, t_list *mtl_ids, int index)
{
	t_material	*material;
	t_mesh		*mesh;
	t_vec3		anchor_point;
	t_vec3		scale;
	t_quat		rotation;

	material = get_material(values[5], context->scene->materials, mtl_ids);
	if (!material)
		return (0);
	anchor_point = get_vec3(values[1]);
	scale = get_vec3(values[2]);
	rotation = get_quat(values[3]);
	mesh = load_obj(values[4]);
	if (!mesh)
		return (0);
	context->scene->objects[index] = create_mesh(anchor_point, scale, &rotation,
			mesh);
	if (!context->scene->objects[index].type)
		return (0);
	context->scene->objects[index].material = material;
	return (1);
}
