/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:30:43 by fmol              #+#    #+#             */
/*   Updated: 2025/02/12 13:16:38 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	to_radians(float degrees)
{
	return (degrees * M_PI / 180.0);
}

float	to_degrees(float radians)
{
	return (radians * 180.0 / M_PI);
}
