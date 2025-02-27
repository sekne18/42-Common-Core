/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_validators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:42:07 by jans              #+#    #+#             */
/*   Updated: 2025/02/17 11:17:21 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * Validates values for sphere
 * Values for sphere are: [name] [x],[y],[z] [diameter] [mtl_name]
 * Range of values: INT_MIN <= x,y,z <= INT_MAX, 0 <= diameter <= FLOAT_MAX, 
 * [mtl_name] is a valid material name
 * RETURNS: 1 if the values are valid, 0 if the values are invalid.
 * */
int	valid_sphere(char **values, t_list *mtl_ids)
{
	if (ft_split_size(values) != 4)
		return (0);
	if (!valid_coordinates(values[1]))
		return (0);
	if (!ft_isfloat(values[2]) || ft_atof(values[2]) <= 0)
		return (0);
	if (!valid_material_id(values[3], mtl_ids))
		return (0);
	return (1);
}

/*
 * Validates values for cylinder

 * Values for cylinder are:
 * [name] [x],[y],[z] [normalized_vec] [diameter] [height] [mtl_name]
 * Range of values: INT_MIN <= x,y,z <= INT_MAX, -1 <= normalized_vec <= 1,0 
 * <= diameter, height <= FLOAT_MAX, [mtl_name] is a valid material name
 * RETURNS: 1 if the values are valid, 0 if the values are invalid.
 * */
int	valid_cylinder(char **values, t_list *mtl_ids)
{
	if (ft_split_size(values) != 6)
		return (0);
	if (!valid_coordinates(values[1]))
		return (0);
	if (!valid_normalized_vec(values[2]))
		return (0);
	if (!ft_isfloat(values[3]) || ft_atof(values[3]) <= 0)
		return (0);
	if (!ft_isfloat(values[4]) || ft_atof(values[4]) <= 0)
		return (0);
	if (!valid_material_id(values[5], mtl_ids))
		return (0);
	return (1);
}

/*
 * Validates values for triangle
 * Values for triangle are: 
 * [name] [x],[y],[z] [x],[y],[z] [x],[y],[z] [mtl_name]
 * RETURNS: 1 if the values are valid, 0 if the values are invalid
 * */
int	valid_triangle(char **values, t_list *mtl_ids)
{
	if (ft_split_size(values) != 5)
		return (0);
	if (!valid_coordinates(values[1]))
		return (0);
	if (!valid_coordinates(values[2]))
		return (0);
	if (!valid_coordinates(values[3]))
		return (0);
	if (!valid_material_id(values[4], mtl_ids))
		return (0);
	return (1);
}

/*
 * Validates values for square
 * Values for square are: [name] [x],[y],[z] [x],[y],[z] [side_size] [mtl_name]
 * RETURNS: 1 if the values are valid, 0 if the values are invalid.
 * */
int	valid_square(char **values, t_list *mtl_ids)
{
	if (ft_split_size(values) != 5)
		return (0);
	if (!valid_coordinates(values[1]))
		return (0);
	if (!valid_coordinates(values[2]))
		return (0);
	if (!valid_coordinates(values[3]))
		return (0);
	if (!valid_material_id(values[4], mtl_ids))
		return (0);
	return (1);
}

/*
* Validates values for a disk
* Values for disk are: [name] [x],[y],[z] [normalized_vec] [radius] [mtl_name]
*/
int	valid_disk(char **values, t_list *mtl_ids)
{
	if (ft_split_size(values) != 5)
		return (0);
	if (!valid_coordinates(values[1]))
		return (0);
	if (!valid_normalized_vec(values[2]))
		return (0);
	if (!ft_isfloat(values[3]) || ft_atof(values[3]) <= 0)
		return (0);
	if (!valid_material_id(values[4], mtl_ids))
		return (0);
	return (1);
}
