/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_bvh_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:24:33 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 16:10:17 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

unsigned int	calc_mesh_depth(t_mesh_bvh *bvh, unsigned int node,
	unsigned int depth)
{
	if (depth == (unsigned int)-1)
		return (0);
	if (bvh->nodes[node].left == 0)
		return (depth);
	return (fmax(calc_mesh_depth(bvh, bvh->nodes[node].left, depth + 1),
			calc_mesh_depth(bvh, bvh->nodes[node].right, depth + 1)));
}

unsigned int	calc_max_mesh_depth(t_bvh *bvh)
{
	unsigned int	i;
	unsigned int	max_depth;
	unsigned int	depth;

	i = 0;
	max_depth = 0;
	while (i < bvh->mesh_count)
	{
		depth = calc_mesh_depth((bvh->mesh_bvhs + i), 0, 0);
		if (depth > max_depth)
			max_depth = depth;
		i++;
	}
	return (max_depth);
}

unsigned int	largest_node_count_meshes(t_bvh *bvh)
{
	unsigned int	i;
	unsigned int	max_count;
	unsigned int	count;

	i = 0;
	max_count = 0;
	while (i < bvh->mesh_count)
	{
		count = bvh->mesh_bvhs[i].node_count;
		if (count > max_count)
			max_count = count;
		i++;
	}
	return (max_count);
}

void	cleanup_mesh_bvh(t_mesh_bvh *mesh_bvh)
{
	unsigned int	i;

	if (!mesh_bvh)
		return ;
	if (mesh_bvh->nodes)
	{
		i = 0;
		while (i < mesh_bvh->node_count)
		{
			if (mesh_bvh->nodes[i].primitives)
				free(mesh_bvh->nodes[i].primitives);
			i++;
		}
		free(mesh_bvh->nodes);
	}
	if (mesh_bvh->centers)
		free(mesh_bvh->centers);
	if (mesh_bvh->bboxes)
		free(mesh_bvh->bboxes);
}
