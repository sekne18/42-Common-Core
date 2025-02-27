/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_children.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:08:03 by jsekne            #+#    #+#             */
/*   Updated: 2025/02/18 16:08:04 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	grow_bboxes(const t_split_primitives_params *params, t_scene *scene,
		unsigned int *left_count, unsigned int *right_count)
{
	unsigned int	j;

	j = 0;
	while (j < params->node->primitive_count)
	{
		if (scene->objects[params->node->primitives[j]].center
			.v[params->best_axis] < params->split_pos)
		{
			params->left->primitives[*left_count] = params->node->primitives[j];
			grow_to_include_bbox(&params->left->bbox,
				&scene->objects[params->node->primitives[j]].bbox);
			(*left_count)++;
		}
		else
		{
			params->right->primitives[*right_count] = params->node
				->primitives[j];
			grow_to_include_bbox(&params->right->bbox,
				&scene->objects[params->node->primitives[j]].bbox);
			(*right_count)++;
		}
		j++;
	}
}

int	allocate_primitives(t_bvh_node *left, t_bvh_node *right,
		unsigned int left_count, unsigned int right_count)
{
	left->primitive_count = left_count;
	left->primitives = malloc(sizeof(unsigned int) * left_count);
	if (!left->primitives)
		return (0);
	right->primitive_count = right_count;
	right->primitives = malloc(sizeof(unsigned int) * right_count);
	if (!right->primitives)
		return (0);
	return (1);
}

void	count_primitives(const t_split_primitives_params *params,
						const t_scene *scene,
						unsigned int *left_count,
						unsigned int *right_count)
{
	unsigned int	j;

	*left_count = 0;
	*right_count = 0;
	j = 0;
	while (j < params->node->primitive_count)
	{
		if (scene->objects[params->node->primitives[j]].center
			.v[params->best_axis] < params->split_pos)
			(*left_count)++;
		else
			(*right_count)++;
		j++;
	}
}

int	add_children(unsigned int i, t_scene *scene, int best_axis, float split_pos)
{
	t_bvh_node		*node;
	t_bvh_node		left;
	t_bvh_node		right;
	unsigned int	left_count;
	unsigned int	right_count;

	node = &scene->bvh->nodes[i];
	count_primitives(&(t_split_primitives_params){node, NULL, split_pos,
		best_axis, &left, &right}, scene, &left_count, &right_count);
	allocate_primitives(&left, &right, left_count, right_count);
	left_count = 0;
	right_count = 0;
	left.bbox = (t_aabb){(t_vec3){{INFINITY, INFINITY, INFINITY}},
		(t_vec3){{-INFINITY, -INFINITY, -INFINITY}}};
	right.bbox = (t_aabb){(t_vec3){{INFINITY, INFINITY, INFINITY}},
		(t_vec3){{-INFINITY, -INFINITY, -INFINITY}}};
	grow_bboxes(&(t_split_primitives_params){node, NULL, split_pos, best_axis,
		&left, &right}, scene, &left_count, &right_count);
	pad(&left.bbox, BBOX_PADDING);
	pad(&right.bbox, BBOX_PADDING);
	node->left = scene->bvh->node_count;
	scene->bvh->nodes[scene->bvh->node_count++] = left;
	node->right = scene->bvh->node_count;
	scene->bvh->nodes[scene->bvh->node_count++] = right;
	return (1);
}

/*
 int	add_children(unsigned int i, t_scene *scene, 
 int best_axis, float split_pos)
{
	t_bvh_node		*node;
	t_bvh_node		left;
	t_bvh_node		right;
	unsigned int	j;
	unsigned int	left_count;
	unsigned int	right_count;

	node = &scene->bvh->nodes[i];
	left_count = 0;
	right_count = 0;
	// Put into a function
	j = 0;
	while (j < node->primitive_count)
	{
		if (scene->objects[node->primitives[j]].center.v[best_axis] < split_pos)
			left_count++;
		else
			right_count++;
		j++;
	}
	// Put into a function
	left.primitive_count = left_count;
	left.primitives = malloc(sizeof(unsigned int) * left_count);
	if (!left.primitives)
		return (0);
	right.primitive_count = right_count;
	right.primitives = malloc(sizeof(unsigned int) * right_count);
	if (!right.primitives)
		return (0);
	j = 0;
	// Put into a function
	left_count = 0;
	right_count = 0;
	left.bbox = (t_aabb){(t_vec3){{INFINITY, INFINITY, INFINITY}},
		(t_vec3){{-INFINITY, -INFINITY, -INFINITY}}};
	right.bbox = (t_aabb){(t_vec3){{INFINITY, INFINITY, INFINITY}},
		(t_vec3){{-INFINITY, -INFINITY, -INFINITY}}};
	// Put into a function
	while (j < node->primitive_count)
	{
		if (scene->objects[node->primitives[j]].center.v[best_axis] < split_pos)
		{
			left.primitives[left_count++] = node->primitives[j];
			grow_to_include_bbox(&left.bbox,
				&scene->objects[node->primitives[j]].bbox);
		}
		else
		{
			right.primitives[right_count++] = node->primitives[j];
			grow_to_include_bbox(&right.bbox,
				&scene->objects[node->primitives[j]].bbox);
		}
		j++;
	}
	pad(&left.bbox, BBOX_PADDING);
	pad(&right.bbox, BBOX_PADDING);
	node->left = scene->bvh->node_count;
	scene->bvh->nodes[scene->bvh->node_count++] = left;
	node->right = scene->bvh->node_count;
	scene->bvh->nodes[scene->bvh->node_count++] = right;
	return (1);
}
 */
