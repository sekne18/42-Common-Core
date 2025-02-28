/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_bvh_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:57:34 by jsekne            #+#    #+#             */
/*   Updated: 2025/02/18 11:57:35 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	subdivide_mesh_bvh(unsigned int i, t_mesh_bvh *mesh_bvh,
		unsigned int max_nodes)
{
	t_bvh_node	*node;
	float		split_pos;
	int			best_axis;
	float		parent_cost;

	node = mesh_bvh->nodes + i;
	node->left = 0;
	node->right = 0;
	parent_cost = surface_area(&node->bbox) * node->primitive_count;
	if (node->primitive_count <= MAX_PRIMITIVES)
		return (1);
	best_axis = calc_mesh_best_axis(node, mesh_bvh, &split_pos, parent_cost);
	if (best_axis == -1)
		return (1);
	if (mesh_bvh->node_count + 2 > max_nodes)
		return (0);
	if (!add_children_mesh(i, mesh_bvh, best_axis, split_pos))
		return (0);
	return (subdivide_mesh_bvh(node->left, mesh_bvh, max_nodes)
		&& subdivide_mesh_bvh(node->right, mesh_bvh, max_nodes));
}

int	compute_face_centers(t_mesh *mesh, t_mesh_bvh *mesh_bvh)
{
	unsigned int	i;
	float			one_over_3;

	mesh_bvh->centers = malloc(sizeof(t_vec3) * mesh->face_count);
	if (!mesh_bvh->centers)
		return (0);
	i = 0;
	one_over_3 = 1.0 / 3.0;
	while (i < mesh->face_count)
	{
		mesh_bvh->centers[i] = (t_vec3){{0, 0, 0}};
		add_local(&mesh_bvh->centers[i],
			&mesh->vertices[mesh->faces[i].vertices[0]]);
		add_local(&mesh_bvh->centers[i],
			&mesh->vertices[mesh->faces[i].vertices[1]]);
		add_local(&mesh_bvh->centers[i],
			&mesh->vertices[mesh->faces[i].vertices[2]]);
		mul_scalar_local(&mesh_bvh->centers[i], one_over_3);
		i++;
	}
	return (1);
}

int	compute_face_bboxes(t_mesh *mesh, t_mesh_bvh *mesh_bvh)
{
	unsigned int	i;

	mesh_bvh->bboxes = malloc(sizeof(t_aabb) * mesh->face_count);
	if (!mesh_bvh->bboxes)
		return (0);
	i = 0;
	while (i < mesh->face_count)
	{
		mesh_bvh->bboxes[i].min = (t_vec3){{INFINITY, INFINITY, INFINITY}};
		mesh_bvh->bboxes[i].max = (t_vec3){{-INFINITY, -INFINITY, -INFINITY}};
		grow_to_include_face(&mesh_bvh->bboxes[i], mesh->vertices,
			mesh->faces[i].vertices);
		pad(&mesh_bvh->bboxes[i], BBOX_PADDING);
		i++;
	}
	return (1);
}

int	build_mesh_bvh(t_scene *scene, unsigned int mesh_i)
{
	t_mesh_bvh		*mesh_bvh;
	t_mesh			*mesh;
	unsigned int	max_nodes;

	mesh = (scene->objects + mesh_i)->data;
	mesh_bvh = scene->bvh->mesh_bvhs + mesh_i;
	max_nodes = 2 * mesh->face_count - 1;
	mesh_bvh->nodes = malloc(sizeof(t_bvh_node) * max_nodes);
	mesh_bvh->node_count = 1;
	if (!mesh_bvh->nodes)
		return (0);
	if (!compute_face_centers(mesh, mesh_bvh))
		return (cleanup_mesh_bvh(mesh_bvh), 0);
	if (!compute_face_bboxes(mesh, mesh_bvh))
		return (cleanup_mesh_bvh(mesh_bvh), 0);
	if (!set_root_bvh_mesh(scene, mesh_i) || !subdivide_mesh_bvh(0, mesh_bvh,
			max_nodes))
		return (cleanup_mesh_bvh(mesh_bvh), 0);
	free(mesh_bvh->centers);
	mesh_bvh->centers = NULL;
	free(mesh_bvh->bboxes);
	mesh_bvh->bboxes = NULL;
	return (1);
}
