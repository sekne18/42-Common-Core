/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:47:27 by fmol              #+#    #+#             */
/*   Updated: 2025/02/19 09:24:36 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	set_root_bvh_mesh(t_scene *scene, unsigned int mesh_i)
{
	t_mesh			*mesh;
	t_mesh_bvh		*mesh_bvh;
	t_bvh_node		node;
	unsigned int	i;

	mesh = (scene->objects + mesh_i)->data;
	mesh_bvh = scene->bvh->mesh_bvhs + mesh_i;
	node.primitive_count = mesh->face_count;
	node.primitives = malloc(sizeof(unsigned int) * node.primitive_count);
	if (!node.primitives)
		return (0);
	node.bbox.min = (t_vec3){{INFINITY, INFINITY, INFINITY}};
	node.bbox.max = (t_vec3){{-INFINITY, -INFINITY, -INFINITY}};
	i = 0;
	while (i < mesh->face_count)
	{
		node.primitives[i] = i;
		grow_to_include_bbox(&node.bbox, mesh_bvh->bboxes + i);
		i++;
	}
	pad(&node.bbox, BBOX_PADDING);
	mesh_bvh->nodes[0] = node;
	return (1);
}

float	calc_mesh_sah(t_mesh_bvh *mesh, t_bvh_node *node, int axis,
		float split_pos)
{
	t_aabb			left_bbox;
	t_aabb			right_bbox;
	unsigned int	left_count;
	unsigned int	right_count;
	unsigned int	i;

	init_values(&left_bbox, &right_bbox, &left_count, &right_count);
	i = (unsigned int)-1;
	while (++i < node->primitive_count)
	{
		if (mesh->centers[node->primitives[i]].v[axis] < split_pos)
		{
			left_count++;
			grow_to_include_bbox(&left_bbox, mesh->bboxes
				+ node->primitives[i]);
		}
		else
		{
			right_count++;
			grow_to_include_bbox(&right_bbox, mesh->bboxes
				+ node->primitives[i]);
		}
	}
	return (surface_area(&left_bbox) * left_count + surface_area(&right_bbox)
		* right_count);
}

static int	find_best_axis(t_bvh_node *node, t_mesh_bvh *mesh, float *split_pos,
		float *best_cost)
{
	int				axis;
	unsigned int	i;
	float			curr_pos;
	float			cost;
	int				best_axis;

	best_axis = -1;
	axis = -1;
	while (++axis < 3)
	{
		i = (unsigned int)-1;
		while (++i < node->primitive_count)
		{
			curr_pos = mesh->centers[node->primitives[i]].v[axis];
			cost = calc_mesh_sah(mesh, node, axis, curr_pos);
			if (cost < *best_cost)
			{
				*best_cost = cost;
				best_axis = axis;
				*split_pos = curr_pos;
			}
		}
	}
	return (best_axis);
}

int	calc_mesh_best_axis(t_bvh_node *node, t_mesh_bvh *mesh, float *split_pos,
		float parent_cost)
{
	int		best_axis;
	float	best_cost;

	best_cost = INFINITY;
	best_axis = find_best_axis(node, mesh, split_pos, &best_cost);
	if (best_cost >= parent_cost)
		return (-1);
	return (best_axis);
}
