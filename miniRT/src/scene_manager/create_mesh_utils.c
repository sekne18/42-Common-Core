/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mesh_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:35:28 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 16:39:49 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_vec3	get_mesh_center(t_mesh *mesh)
{
	t_vec3			center;
	unsigned int	i;

	i = 0;
	center = (t_vec3){{0, 0, 0}};
	while (i < mesh->vertex_count)
	{
		add_local(&center, &mesh->vertices[i]);
		i++;
	}
	if (mesh->vertex_count)
		div_scalar_local(&center, mesh->vertex_count);
	return (center);
}

void	destroy_mesh(t_mesh *mesh)
{
	free(mesh->vertices);
	free(mesh->normals);
	free(mesh->faces);
	free(mesh->face_edges);
	free(mesh);
}
