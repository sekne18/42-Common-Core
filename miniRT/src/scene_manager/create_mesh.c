/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mesh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:34:21 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 16:41:40 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	translate_mesh(t_mesh *mesh, t_vec3 translation)
{
	unsigned int	i;

	i = 0;
	while (i < mesh->vertex_count)
	{
		add_local(&mesh->vertices[i], &translation);
		i++;
	}
}

//what about normals?
void	rotate_mesh(t_mesh *mesh, t_quat *rotation)
{
	unsigned int	i;

	i = 0;
	while (i < mesh->vertex_count)
	{
		mesh->vertices[i] = rotate_vec(&mesh->vertices[i], rotation);
		i++;
	}
}

void	scale_mesh(t_mesh *mesh, t_vec3 scale)
{
	unsigned int	i;

	i = 0;
	while (i < mesh->vertex_count)
	{
		mul_local(&mesh->vertices[i], &scale);
		i++;
	}
}

int	compute_normals(t_mesh *mesh)
{
	unsigned int	i;
	t_vec3			edges[2];
	t_vec3			normal;

	mesh->normals = malloc(sizeof(t_vec3) * mesh->face_count);
	if (!mesh->normals)
		return (0);
	mesh->face_edges = malloc(sizeof(t_vec3) * mesh->face_count * 2);
	if (!mesh->face_edges)
		return (0);
	i = 0;
	while (i < mesh->face_count)
	{
		sub(edges, &mesh->vertices[mesh->faces[i].vertices[1]],
			&mesh->vertices[mesh->faces[i].vertices[0]]);
		sub(edges + 1, &mesh->vertices[mesh->faces[i].vertices[2]],
			&mesh->vertices[mesh->faces[i].vertices[0]]);
		mesh->face_edges[i * 2] = edges[0];
		mesh->face_edges[i * 2 + 1] = edges[1];
		cross(&normal, edges, edges + 1);
		normalize_local(&normal);
		mesh->normals[i] = normal;
		i++;
	}
	return (1);
}

t_object	create_mesh(t_vec3 anchor_point, t_vec3 scale,
	t_quat *rotation, t_mesh *mesh)
{
	t_vec3	center;

	if (!mesh)
		return ((t_object){0});
	rotate_mesh(mesh, rotation);
	scale_mesh(mesh, scale);
	translate_mesh(mesh, anchor_point);
	center = get_mesh_center(mesh);
	if (!compute_normals(mesh))
		return (destroy_mesh(mesh), (t_object){0});
	return ((t_object){NULL, MESH, get_mesh_aabb(mesh),
		center, mesh});
}
