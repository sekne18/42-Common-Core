/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:42:14 by jans              #+#    #+#             */
/*   Updated: 2025/02/19 10:21:29 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	handle_material(char *line, t_list **mtl_ids)
{
	if (save_material_id(line, mtl_ids) != SUCCESS)
		return (free(line), ERR_MEM);
	if (contains_duplicate_ids(*mtl_ids))
		return (free(line), ERR_DUP_MTL);
	return (SUCCESS);
}

static int	process_line(char *line, t_obj_count *obj_counts, t_list **mtl_ids)
{
	int	status;

	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (!ft_strcmp(line, "\n") || line[0] == '#' || !line[0])
		return (free(line), SUCCESS);
	status = inc_obj_count(line, obj_counts);
	if (status != SUCCESS)
		return (free(line), status);
	if (parse_type(line) == P_MATERIAL)
	{
		status = handle_material(line, mtl_ids);
		if (status != SUCCESS)
			return (status);
	}
	free(line);
	return (SUCCESS);
}

static int	process_lines(int fd, t_obj_count *obj_counts, t_list **mtl_ids)
{
	char	*line;
	int		status;

	line = get_next_line(fd);
	while (line != NULL)
	{
		status = process_line(line, obj_counts, mtl_ids);
		if (status != SUCCESS)
			return (status);
		line = get_next_line(fd);
	}
	return (SUCCESS);
}

static int	initialize_scene(t_context *context, t_obj_count *obj_counts)
{
	context->scene->object_count = obj_counts->obj_count
		+ obj_counts->plane_count + obj_counts->mesh_count;
	context->scene->mesh_count = obj_counts->mesh_count;
	context->scene->plane_count = obj_counts->plane_count;
	if (!context->scene->object_count || !obj_counts->mat_count)
		return (ERR_NO_OBJ);
	context->scene->material_count = obj_counts->mat_count;
	context->scene->materials = malloc(sizeof(t_material)
			* obj_counts->mat_count);
	if (!context->scene->materials)
		return (ERR_MEM);
	context->scene->objects = malloc(sizeof(t_object)
			* context->scene->object_count);
	if (!context->scene->objects)
		return (ERR_MEM);
	return (SUCCESS);
}

/*
 * First pass of the file should count and allocate materials,
	meshes and objects.
 * It should also validate the line format depending on the type.
 * RETURN: 1 if the file is valid, 0 if the file is invalid.
 * */
int	first_pass(t_context *context, char *filename, t_obj_count *obj_counts,
		t_list **mtl_ids)
{
	int	fd;
	int	result;

	set_obj_count(obj_counts);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ERR_FILE);
	result = process_lines(fd, obj_counts, mtl_ids);
	close(fd);
	if (result != SUCCESS)
		return (result);
	return (initialize_scene(context, obj_counts));
}
