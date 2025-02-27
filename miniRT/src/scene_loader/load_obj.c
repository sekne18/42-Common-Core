/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:21:21 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 11:59:39 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

int	alloc_mesh_arrays(t_mesh *mesh)
{
	mesh->vertices = malloc(sizeof(t_vec3) * mesh->vertex_count);
	mesh->normals = NULL;
	mesh->faces = malloc(sizeof(t_face) * mesh->face_count);
	if (mesh->vertices && mesh->faces)
		return (1);
	free(mesh->vertices);
	free(mesh->faces);
	mesh->vertices = NULL;
	mesh->faces = NULL;
	return (0);
}

int	init_mesh(t_mesh *mesh, FILE *file)
{
	char	line[MAX_LINE_LENGTH];

	ft_memset(mesh, 0, sizeof(t_mesh));
	while (fgets(line, MAX_LINE_LENGTH, file))
	{
		if (line[0] == 'v' && line[1] == ' ')
			mesh->vertex_count++;
		else if (line[0] == 'v' && line[1] == 'n')
			mesh->normal_count++;
		else if (line[0] == 'v' && line[1] == 't')
			mesh->uv_count++;
		else if (line[0] == 'f' && line[1] == ' ')
			mesh->face_count++;
	}
	if (alloc_mesh_arrays(mesh))
		return (1);
	return (0);
}

int	set_mesh_data(t_mesh *mesh, FILE *file)
{
	char	line[MAX_LINE_LENGTH];
	int		indices[4];
	int		face_indices[3];

	ft_memset(indices, 0, sizeof(int) * 4);
	while (fgets(line, MAX_LINE_LENGTH, file))
	{
		if (sscanf(line, "v %f %f %f \n", &mesh->vertices[indices[0]].x,
				&mesh->vertices[indices[0]].y, &mesh->vertices[indices[0]].z))
			indices[0]++;
		else if (sscanf(line, "f %d %d %d \n", &face_indices[0],
				&face_indices[1], &face_indices[2]))
		{
			mesh->faces[indices[3]].vertices[0] = face_indices[0] - 1;
			mesh->faces[indices[3]].vertices[1] = face_indices[1] - 1;
			mesh->faces[indices[3]].vertices[2] = face_indices[2] - 1;
			indices[3]++;
		}
	}
	return (1);
}

/*TODO: set get_next_line buffer size to a big number to avoid multiple reads*/
t_mesh	*load_obj(char *filename)
{
	t_mesh	*mesh;
	FILE	*file;

	file = fopen(filename, "r");
	if (!file)
		return (NULL);
	mesh = malloc(sizeof(t_mesh));
	if (!mesh)
		return (fclose(file), NULL);
	if (!init_mesh(mesh, file))
		return (fclose(file), destroy_mesh(mesh), NULL);
	rewind(file);
	if (!set_mesh_data(mesh, file))
		return (fclose(file), destroy_mesh(mesh), NULL);
	return (fclose(file), mesh);
}
