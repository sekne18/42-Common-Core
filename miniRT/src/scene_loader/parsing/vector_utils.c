/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:42:37 by jans              #+#    #+#             */
/*   Updated: 2025/02/13 13:22:05 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * PARAMETHERS: Coordinates
 * DESCRIPTION: Splits the coordinates by , and creates a vector
 * RETURNS: Coordinate vector.
 * */
t_vec3	get_vec3(char *coordinates)
{
	char	**split;
	t_vec3	vec;

	split = ft_split(coordinates, ',');
	if (!split)
		return ((t_vec3){{0, 0, 0}});
	vec.x = ft_atof(split[0]);
	vec.y = ft_atof(split[1]);
	vec.z = ft_atof(split[2]);
	ft_free_split(split);
	return (vec);
}

t_quat	get_quat(char *coordinates)
{
	char	**split;
	t_quat	quat;

	split = ft_split(coordinates, ',');
	if (!split)
		return ((t_quat){0, 0, 0, 1});
	quat.x = ft_atof(split[0]);
	quat.y = ft_atof(split[1]);
	quat.z = ft_atof(split[2]);
	quat.w = ft_atof(split[3]);
	ft_free_split(split);
	return (quat);
}

/*
 * PARAMETHERS: Normalized string vector
 * DESCRIPTION: Splits the coordinates by , and creates a normalized vector
 * RETURNS: Normalized vector.
 * */
t_vec3	get_remapped_color(char *color)
{
	t_vec3	vec;

	vec = get_vec3(color);
	vec = remap_color(vec);
	return (vec);
}

/*
 * PARAMETHERS: vector
 * DESCRIPTION: Normalize the vector
 * RETURNS: Normalized vector.
 * */
t_vec3	remap_color(t_vec3 vec)
{
	float	len;

	len = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (len == 0.0f)
		return ((t_vec3){{0, 0, 0}});
	vec.x /= 255.0f;
	vec.y /= 255.0f;
	vec.z /= 255.0f;
	return (vec);
}

int	valid_normalized_vec(char *value)
{
	char	**split;
	int		i;

	i = -1;
	split = ft_split(value, ',');
	if (!split)
		return (0);
	if (ft_split_size(split) != 3)
		return (ft_free_split(split), 0);
	while (split[++i])
	{
		if (ft_atof(split[i]) < -1 || ft_atof(split[i]) > 1)
			return (ft_free_split(split), 0);
	}
	return (ft_free_split(split), 1);
}
