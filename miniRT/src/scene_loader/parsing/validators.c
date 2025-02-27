/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:42:27 by jans              #+#    #+#             */
/*   Updated: 2025/02/13 13:38:22 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	valid_material_type(char **values, int size, int i)
{
	if (!ft_strcmp(values[i], "NULL") && size == 11)
		return (1);
	if ((!ft_strcmp(values[i], "TXT") || !ft_strcmp(values[i], "BUMP"))
		&& size == 12)
		return (1);
	if (!ft_strcmp(values[i], "TXT_BUMP") && size == 13)
		return (1);
	if (!ft_strcmp(values[i], "CHECKER") && size == 13 && valid_rgb(values[11])
		&& valid_rgb(values[12]))
		return (1);
	return (0);
}

int	valid_material(char **values)
{
	int	i;
	int	size;

	i = 1;
	size = ft_split_size(values);
	if (size < 11)
		return (0);
	while (i < 5)
	{
		if (!valid_rgb(values[i]))
			return (0);
		i++;
	}
	while (i < 10)
	{
		if (!ft_isfloat(values[i]) || ft_atof(values[i]) < 0)
			return (0);
		i++;
	}
	return (valid_material_type(values, size, i));
}

/*
 * Validates values for camera
 *
 * Valid format of values for camera is: [name] [x],[y],[z] [x],[y],[z] [FOV]
 * Range of values: INT_MIN <= x,y,z <= INT_MAX, -1 <= x,y,z <= 1,
	0 <= FOV <= 180
 * RETURNS: 1 if the values are valid, 0 if the values are invalid.
 * */
int	valid_camera(char **values)
{
	int		i;
	float	fov;

	i = 1;
	if (ft_split_size(values) != 4)
		return (0);
	if (!valid_coordinates(values[i]))
		return (0);
	i++;
	if (!valid_normalized_vec(values[i]))
		return (0);
	i++;
	if (!ft_isfloat(values[i]))
		return (0);
	fov = ft_atof(values[i]);
	if (fov < 0 || fov > 180)
		return (0);
	return (1);
}

/*
 * Validates values for window (size)
 *
 * Valid format of values for window is: [width] [height]
 * Range of values: 0 < width, height <= 2000
 * Check if the values are in the correct format
 * RETURNS: 1 if the values are valid, 0 if the values are invalid.
 * */
int	valid_window(char **values)
{
	int	i;
	int	size;

	i = 1;
	if (ft_split_size(values) != 3)
		return (0);
	if (!ft_isnumber(values[i]))
		return (0);
	size = ft_atoi(values[i]);
	if (size <= 0 || size > 2000)
		return (0);
	i++;
	if (!ft_isnumber(values[i]))
		return (0);
	size = ft_atoi(values[i]);
	if (size <= 0 || size > 2000)
		return (0);
	return (1);
}

/*
 * Validates values for ambient light
 *
 * Valid format of values for ambient light is:
 * [name] [intensity] [nbr_of_rgs] ([r],[g],[b] * nbr_of_rgs)
 * Range of values:
 * 0 <= r,g,b <= 255, 0 <= intensity <= 1,0 <= nbr_of_rgs <= unsigned_int_max
 * Check if the values are in the correct format and the numbers of rgb values 
 * are correct
 * i - 3 to ignore first 3 values
 * RETURNS: 1 if the values are valid, 0 if the values are invalid.
 * */
int	valid_amb_light(char **values)
{
	int	i;
	int	nbr_of_rgbs;

	i = 1;
	if (!ft_isfloat(values[i]) || ft_atof(values[i]) < 0
		|| ft_atof(values[i]) > 1)
		return (0);
	i++;
	if (!ft_isnumber(values[i]))
		return (0);
	nbr_of_rgbs = ft_atoi(values[i]);
	if (nbr_of_rgbs < 1)
		return (0);
	i++;
	if (ft_split_size(values) - 3 != nbr_of_rgbs)
		return (0);
	while (i - 3 < nbr_of_rgbs)
	{
		if (!valid_rgb(values[i]))
			return (0);
		i++;
	}
	return (1);
}
