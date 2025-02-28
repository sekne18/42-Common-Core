/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:33:01 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 16:09:35 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	cleanup_objects(t_object *objects, unsigned int object_count)
{
	unsigned int	i;

	i = 0;
	while (i < object_count)
	{
		if (objects[i].type == MESH)
			destroy_mesh(objects[i].data);
		else
			free(objects[i].data);
		i++;
	}
	free(objects);
}

void	cleanup_scene(t_scene *scene)
{
	unsigned int	i;

	if (!scene)
		return ;
	cleanup_bvh(scene->bvh);
	if (scene->objects)
		cleanup_objects(scene->objects, scene->object_count);
	if (scene->materials)
	{
		i = 0;
		while (i < scene->material_count)
		{
			if (scene->materials[i].texture)
				destroy_texture(scene->materials[i].texture);
			i++;
		}
		free(scene->materials);
	}
	free(scene->amb_light);
	free(scene);
}

int	init_scene(t_scene *scene)
{
	ft_memset(scene, 0, sizeof(t_scene));
	return (0);
}
