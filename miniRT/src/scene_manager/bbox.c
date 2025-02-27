/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bbox.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:15:21 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 16:30:54 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_aabb	get_plane_aabb(t_plane *plane)
{
	t_aabb	bbox;

	(void)plane;
	bbox.min = (t_vec3){{-INFINITY, -INFINITY, -INFINITY}};
	bbox.max = (t_vec3){{INFINITY, INFINITY, INFINITY}};
	return (bbox);
}

t_aabb	get_mesh_aabb(t_mesh *mesh)
{
	t_aabb			bbox;
	unsigned int	i;

	bbox.min = (t_vec3){{INFINITY, INFINITY, INFINITY}};
	bbox.max = (t_vec3){{-INFINITY, -INFINITY, -INFINITY}};
	i = 0;
	while (i < mesh->vertex_count)
	{
		min_local(&bbox.min, &mesh->vertices[i]);
		max_local(&bbox.max, &mesh->vertices[i]);
		i++;
	}
	pad(&bbox, BBOX_PADDING);
	return (bbox);
}

void	grow_to_include_face(t_aabb *bbox, t_vec3 *vertices,
	unsigned int *indices)
{
	unsigned int	i;

	i = 0;
	while (i < 3)
	{
		min_local(&bbox->min, &vertices[indices[i]]);
		max_local(&bbox->max, &vertices[indices[i]]);
		i++;
	}
}

void	grow_to_include_bbox(t_aabb *bbox, t_aabb *c1)
{
	min_local(&bbox->min, &c1->min);
	max_local(&bbox->max, &c1->max);
}
