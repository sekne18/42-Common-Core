/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:42:21 by jans              #+#    #+#             */
/*   Updated: 2025/02/13 13:30:09 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/*
 * Validate number for rgb values
 * Allowed values: 0 <= r,g,b <= 255
 * RETURNS: 1 if the values are valid, 0 if the values are invalid.
 * */
int	valid_rgb(char *value)
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
		if (!ft_isnumber(split[i]))
			return (ft_free_split(split), 0);
		if (!valid_rgb_value(split[i]))
			return (ft_free_split(split), 0);
	}
	return (ft_free_split(split), 1);
}

/*
 * Validates values for coordiantes
 *
 * Valid format of values for coordiantes is: [x],[y],[z]
 * Range of values: INT_MIN <= x,y,z <= INT_MAX
 * RETURNS: 1 if the values are valid, 0 if the values are invalid.
 * */
int	valid_coordinates(char *value)
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
		if (!ft_isfloat(split[i]))
			return (ft_free_split(split), 0);
	}
	return (ft_free_split(split), 1);
}

int	valid_quat(char *value)
{
	char	**split;
	int		i;

	i = -1;
	split = ft_split(value, ',');
	if (!split)
		return (0);
	if (ft_split_size(split) != 4)
		return (ft_free_split(split), 0);
	while (split[++i])
	{
		if (!ft_isfloat(split[i]))
			return (ft_free_split(split), 0);
	}
	return (ft_free_split(split), 1);
}

int	valid_rgb_value(char *value)
{
	int	val;

	val = ft_atoi(value);
	if (val < 0 || val > 255)
		return (0);
	return (1);
}

int	ft_split_size(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
