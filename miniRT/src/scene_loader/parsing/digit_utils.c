/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:41:39 by jans              #+#    #+#             */
/*   Updated: 2025/02/13 12:09:01 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static float	get_fraction(char *str, int *i)
{
	float	fraction;
	float	divisor;

	fraction = 0.0;
	divisor = 10.0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		fraction += (str[*i] - '0') / divisor;
		divisor *= 10.0;
		(*i)++;
	}
	return (fraction);
}

/*
 * PARAMETHERS: string
 * DESCRIPTION: Converts string to float
 * RETURNS: float value of the string
 * */
float	ft_atof(char *str)
{
	int		i;
	int		sign;
	float	result;

	i = 0;
	sign = 1;
	result = 0.0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
	{
		i++;
		return (sign * (result + get_fraction(str, &i)));
	}
	return (sign * result);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_isfloat(char *str)
{
	int	i;
	int	dot;
	int	sign;

	i = 0;
	dot = 0;
	sign = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		sign++;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (0);
		if (str[i] == '.')
			dot++;
		i++;
	}
	if (dot > 1 || (sign && i == 1))
		return (0);
	return (1);
}
