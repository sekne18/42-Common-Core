/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:14:38 by fmol              #+#    #+#             */
/*   Updated: 2025/02/18 11:27:31 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	set_root_bvh(t_scene *scene)
{
	t_bvh_node		node;
	unsigned int	i;

	node.primitive_count = scene->object_count - scene->plane_count;
	node.primitives = malloc(sizeof(unsigned int) * node.primitive_count);
	if (!node.primitives)
		return (0);
	node.bbox.min = (t_vec3){{INFINITY, INFINITY, INFINITY}};
	node.bbox.max = (t_vec3){{-INFINITY, -INFINITY, -INFINITY}};
	i = 0;
	while (i < scene->object_count - scene->plane_count)
	{
		node.primitives[i] = i;
		grow_to_include_bbox(&node.bbox, &scene->objects[i].bbox);
		i++;
	}
	pad(&node.bbox, BBOX_PADDING);
	scene->bvh->nodes[0] = node;
	return (1);
}

static inline void	init_calc_sah(t_aabb *left_bbox, t_aabb *right_bbox,
	unsigned int *left_count, unsigned int *right_count)
{
	*left_count = 0;
	*right_count = 0;
	*left_bbox = (t_aabb){(t_vec3){{1e30f, 1e30f, 1e30f}},
		(t_vec3){{-1e30f, -1e30f, -1e30f}}};
	*right_bbox = (t_aabb){(t_vec3){{1e30f, 1e30f, 1e30f}},
		(t_vec3){{-1e30f, -1e30f, -1e30f}}};
}

float	calc_sah(t_scene *scene, t_bvh_node *node, int axis, float split_pos)
{
	t_aabb			left_bbox;
	t_aabb			right_bbox;
	unsigned int	left_count;
	unsigned int	right_count;
	unsigned int	i;

	init_calc_sah(&left_bbox, &right_bbox, &left_count, &right_count);
	i = (unsigned int)-1;
	while (++i < node->primitive_count)
	{
		if (scene->objects[node->primitives[i]].center.v[axis] < split_pos)
		{
			left_count++;
			grow_to_include_bbox(&left_bbox,
				&scene->objects[node->primitives[i]].bbox);
		}
		else
		{
			right_count++;
			grow_to_include_bbox(&right_bbox,
				&scene->objects[node->primitives[i]].bbox);
		}
	}
	return (surface_area(&left_bbox) * left_count
		+ surface_area(&right_bbox) * right_count);
}

int	calc_best_axis(t_bvh_node *node, t_scene *scene,
	float *split_pos, float parent_cost)
{
	int				axis[2];
	t_vec2			cost;
	unsigned int	i;
	float			curr_pos;

	init_calc_best_axis(&cost, axis);
	while (axis[0] < 3)
	{
		i = (unsigned int)-1;
		while (++i < node->primitive_count)
		{
			curr_pos = scene->objects[node->primitives[i]].center.v[axis[0]];
			cost.x = calc_sah(scene, node, axis[0], curr_pos);
			if (cost.x < cost.y)
			{
				*split_pos = curr_pos;
				cost.y = cost.x;
				axis[1] = axis[0];
			}
		}
		(axis[0])++;
	}
	if (cost.y >= parent_cost)
		return (-1);
	return (axis[1]);
}
