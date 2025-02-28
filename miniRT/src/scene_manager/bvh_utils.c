/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:00:07 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 16:10:36 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

unsigned int	calc_depth(t_bvh *bvh, unsigned int node, unsigned int depth)
{
	if (depth == (unsigned int)-1)
		return (0);
	if (bvh->nodes[node].left == 0)
		return (depth);
	return (fmax(calc_depth(bvh, bvh->nodes[node].left, depth + 1),
			calc_depth(bvh, bvh->nodes[node].right, depth + 1)));
}

void	cleanup_nodes(t_bvh_node *nodes, unsigned int node_count)
{
	unsigned int	i;

	i = 0;
	while (i < node_count)
	{
		if (nodes[i].primitives)
			free(nodes[i].primitives);
		i++;
	}
	free(nodes);
}

void	cleanup_bvh(t_bvh *bvh)
{
	unsigned int	i;

	if (!bvh)
		return ;
	if (bvh->nodes)
		cleanup_nodes(bvh->nodes, bvh->node_count);
	if (bvh->mesh_bvhs)
	{
		i = 0;
		while (i < bvh->mesh_count)
		{
			cleanup_mesh_bvh(bvh->mesh_bvhs + i);
			i++;
		}
		free(bvh->mesh_bvhs);
	}
	if (bvh->stack)
		free(bvh->stack);
	free(bvh);
}

void	init_calc_best_axis(t_vec2 *cost, int *axis)
{
	cost->x = INFINITY;
	cost->y = INFINITY;
	axis[0] = 0;
	axis[1] = -1;
}
