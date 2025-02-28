/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_validators2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:00:31 by jans              #+#    #+#             */
/*   Updated: 2025/02/13 13:34:44 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * Validates values for plane
 * Values for plane are: [name] [x],[y],[z] [x],[y],[z] [mtl_name]
 * RETURNS: 1 if the values are valid, 0 if the values are invalid.
 * */
int	valid_plane(char **values, t_list *mtl_ids)
{
	if (ft_split_size(values) != 4)
		return (0);
	if (!valid_coordinates(values[1]))
		return (0);
	if (!valid_normalized_vec(values[2]))
		return (0);
	if (!valid_material_id(values[3], mtl_ids))
		return (0);
	return (1);
}

/*
 * TODO maybe check for valid obj file?
 * */
int	valid_mesh(char **values, t_list *mtl_ids)
{
	if (ft_split_size(values) != 6)
		return (0);
	if (!valid_coordinates(values[1]))
		return (0);
	if (!valid_coordinates(values[2]))
		return (0);
	if (!valid_quat(values[3]))
		return (0);
	if (!valid_material_id(values[5], mtl_ids))
		return (0);
	return (1);
}

/*
 * Validates values for objects
 * Checks for the object type and executes the validation for the object type
 * RETURNS: 1 if the values are valid, 0 if the values are invalid.
 * */
int	valid_object(char **values, t_list *mtl_ids)
{
	if (ft_strcmp(values[0], "sp") == 0)
		return (valid_sphere(values, mtl_ids));
	if (ft_strcmp(values[0], "pl") == 0)
		return (valid_plane(values, mtl_ids));
	if (ft_strcmp(values[0], "sq") == 0)
		return (valid_square(values, mtl_ids));
	if (ft_strcmp(values[0], "cy") == 0)
		return (valid_cylinder(values, mtl_ids));
	if (ft_strcmp(values[0], "tr") == 0)
		return (valid_triangle(values, mtl_ids));
	if (ft_strcmp(values[0], "ds") == 0)
		return (valid_disk(values, mtl_ids));
	if (ft_strcmp(values[0], "obj") == 0)
		return (valid_mesh(values, mtl_ids));
	return (0);
}
