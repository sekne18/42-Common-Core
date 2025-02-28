/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_children_mesh.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:57:22 by jsekne            #+#    #+#             */
/*   Updated: 2025/02/18 11:57:24 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static int	allocate_children_nodes(t_bvh_node *left, t_bvh_node *right,
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

static void	split_primitives(const t_split_primitives_params *params)
{
	unsigned int	j;
	unsigned int	left_count;
	unsigned int	right_count;

	left_count = 0;
	right_count = 0;
	j = (unsigned int)-1;
	while (++j < params->node->primitive_count)
	{
		if (params->mesh_bvh->centers[params->node->primitives[j]]
			.v[params->best_axis] < params->split_pos)
			params->left->primitives[left_count++] = params->node
				->primitives[j];
		else
			params->right->primitives[right_count++] = params->node
				->primitives[j];
	}
}

static void	grow_and_pad_bboxes(const t_split_primitives_params *params)
{
	unsigned int	j;

	j = (unsigned int)-1;
	while (++j < params->left->primitive_count)
		grow_to_include_bbox(&params->left->bbox, params->mesh_bvh->bboxes
			+ params->left->primitives[j]);
	j = (unsigned int)-1;
	while (++j < params->right->primitive_count)
		grow_to_include_bbox(&params->right->bbox, params->mesh_bvh->bboxes
			+ params->right->primitives[j]);
	pad(&params->left->bbox, BBOX_PADDING);
	pad(&params->right->bbox, BBOX_PADDING);
}

static void	count_primitives_in_split(
	const t_split_primitives_params *params, unsigned int *left_count,
	unsigned int *right_count)
{
	unsigned int	j;

	*left_count = 0;
	*right_count = 0;
	j = (unsigned int)-1;
	while (++j < params->node->primitive_count)
	{
		if (params->mesh_bvh->centers[params->node->primitives[j]]
			.v[params->best_axis] < params->split_pos)
			(*left_count)++;
		else
			(*right_count)++;
	}
}

int	add_children_mesh(unsigned int i, t_mesh_bvh *mesh_bvh, int best_axis,
		float split_pos)
{
	t_bvh_node		*node;
	t_bvh_node		left;
	t_bvh_node		right;
	unsigned int	left_count;
	unsigned int	right_count;

	init_values(&left.bbox, &right.bbox, &left_count, &right_count);
	node = mesh_bvh->nodes + i;
	count_primitives_in_split(&(t_split_primitives_params){node, mesh_bvh,
		split_pos, best_axis, NULL, NULL}, &left_count, &right_count);
	if (!allocate_children_nodes(&left, &right, left_count, right_count))
		return (0);
	split_primitives(&(t_split_primitives_params){node, mesh_bvh, split_pos,
		best_axis, &left, &right});
	left.bbox = (t_aabb){{{1e30f, 1e30f, 1e30f}}, {{-1e30f, -1e30f, -1e30f}}};
	right.bbox = (t_aabb){{{1e30f, 1e30f, 1e30f}}, {{-1e30f, -1e30f, -1e30f}}};
	grow_and_pad_bboxes(&(t_split_primitives_params){node, mesh_bvh, split_pos,
		best_axis, &left, &right});
	pad(&left.bbox, BBOX_PADDING);
	pad(&right.bbox, BBOX_PADDING);
	node->left = mesh_bvh->node_count;
	mesh_bvh->nodes[mesh_bvh->node_count++] = left;
	node->right = mesh_bvh->node_count;
	mesh_bvh->nodes[mesh_bvh->node_count++] = right;
	return (1);
}
