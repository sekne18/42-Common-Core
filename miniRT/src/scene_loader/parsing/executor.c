/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:41:47 by jans              #+#    #+#             */
/*   Updated: 2025/02/13 14:31:16 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	process_line(t_context *context, char *line, t_list *mtl_ids,
		t_obj_count *obj_counts)
{
	int	type;

	type = parse_type(line);
	if (!valid_line(type, line, mtl_ids))
		return (ERR_INV_TYPE);
	if (type == P_MATERIAL && !build_materials(context, line, mtl_ids))
		return (ERR_MEM);
	else if (type == P_OBJECT || type == P_MESH || type == P_PLANE)
	{
		if (!build_objects(context, line, mtl_ids, obj_counts))
			return (ERR_MEM);
	}
	else if (type == P_CAMERA && !build_camera(context, line))
		return (ERR_MEM);
	else if (type == P_AMB_LIGHT && !build_amb_light(context, line))
		return (ERR_MEM);
	else if (type == P_WINDOW && !build_window(context, line))
		return (ERR_MEM);
	return (SUCCESS);
}

static int	process_file_line(t_context *context, char *line, t_list *mtl_ids,
		t_obj_count *obj_counts)
{
	int	status;

	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (!ft_strcmp(line, "\n") || line[0] == '#' || !line[0])
		return (free(line), SUCCESS);
	status = process_line(context, line, mtl_ids, obj_counts);
	free(line);
	return (status);
}

/*
 * Validates values of each line and creates objects
 * RETURN: status code
 * */
int	second_pass(t_context *context, char *filename, t_list *mtl_ids,
		t_obj_count *obj_counts)
{
	char	*line;
	int		fd;
	int		status;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		status = process_file_line(context, line, mtl_ids, obj_counts);
		if (status != SUCCESS)
			return (close(fd), status);
		line = get_next_line(fd);
	}
	close(fd);
	return (SUCCESS);
}

int	determine_object_type(char *line)
{
	if (!ft_strncmp(line, "sp", 2))
		return (SPHERE);
	else if (!ft_strncmp(line, "sq", 2))
		return (QUAD);
	else if (!ft_strncmp(line, "cy", 2))
		return (CYLINDER);
	else if (!ft_strncmp(line, "tr", 2))
		return (TRIANGLE);
	else if (!ft_strncmp(line, "ds", 2))
		return (DISK);
	else if (!ft_strncmp(line, "pl", 2))
		return (PLANE);
	else if (!ft_strncmp(line, "obj", 3))
		return (MESH);
	return (-1);
}

/*
 * PARAMETERS: parse_type, line
 * DESCRIPTION: Validates the line format depending on the type.
 * RETURN: 1 if the line is valid, 0 if the line is invalid.
 * */
int	valid_line(t_parse_type type, char *line, t_list *mtl_ids)
{
	char	**split;
	int		status;

	status = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (ERR_MEM);
	if (type == P_MATERIAL)
		status = valid_material(split);
	else if (type == P_CAMERA)
		status = valid_camera(split);
	else if (type == P_AMB_LIGHT)
		status = valid_amb_light(split);
	else if (type == P_WINDOW)
		status = valid_window(split);
	else if (type == P_OBJECT || type == P_MESH || type == P_PLANE)
		status = valid_object(split, mtl_ids);
	return (ft_free_split(split), status);
}
