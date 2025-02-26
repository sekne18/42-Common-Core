/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:07:52 by jsekne            #+#    #+#             */
/*   Updated: 2025/02/18 16:07:53 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	subdivide_bvh(unsigned int i, t_scene *scene, unsigned int max_nodes)
{
	t_bvh_node	*node;
	float		split_pos;
	int			best_axis;
	float		parent_cost;

	node = &scene->bvh->nodes[i];
	node->left = 0;
	node->right = 0;
	parent_cost = surface_area(&node->bbox) * node->primitive_count;
	if (node->primitive_count <= MAX_PRIMITIVES)
		return (1);
	best_axis = calc_best_axis(node, scene, &split_pos, parent_cost);
	if (best_axis == -1)
		return (1);
	if (scene->bvh->node_count + 2 > max_nodes)
		return (0);
	if (!add_children(i, scene, best_axis, split_pos))
		return (0);
	return (subdivide_bvh(node->left, scene, max_nodes)
		&& subdivide_bvh(node->right, scene, max_nodes));
}

int	init_bvh(t_scene *scene)
{
	unsigned int	max_nodes;

	scene->bvh = calloc(1, sizeof(t_bvh));
	if (!scene->bvh)
		return (0);
	max_nodes = 2 * (scene->object_count - scene->plane_count) - 1;
	scene->bvh->nodes = malloc(sizeof(t_bvh_node) * max_nodes);
	if (!scene->bvh->nodes)
		return (0);
	scene->bvh->node_count = 1;
	scene->bvh->mesh_count = scene->mesh_count;
	scene->bvh->mesh_bvhs = NULL;
	if (scene->mesh_count > 0)
		scene->bvh->mesh_bvhs = malloc(sizeof(t_mesh_bvh)
				* scene->bvh->mesh_count);
	if (!scene->bvh->nodes
		|| (scene->bvh->mesh_count > 0 && !scene->bvh->mesh_bvhs))
		return (0);
	if (!set_root_bvh(scene) || !subdivide_bvh(0, scene, max_nodes))
		return (0);
	return (1);
}

int	build_bvh(t_scene *scene)
{
	unsigned int	i;

	if (!init_bvh(scene))
		return (cleanup_bvh(scene->bvh), scene->bvh = NULL, 0);
	i = 0;
	while (i < scene->bvh->mesh_count)
	{
		if (!build_mesh_bvh(scene, i))
			return (cleanup_bvh(scene->bvh), scene->bvh = NULL, 0);
		i++;
	}
	scene->bvh->stack_size = scene->bvh->node_count
		+ largest_node_count_meshes(scene->bvh);
	scene->bvh->stack = malloc(sizeof(unsigned int) * (scene->bvh->stack_size));
	scene->bvh->stack_ptr = 0;
	if (!scene->bvh->stack)
		return (cleanup_bvh(scene->bvh), scene->bvh = NULL, 0);
	return (1);
}
