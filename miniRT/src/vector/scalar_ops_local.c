/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_ops_local.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:41:21 by fmol              #+#    #+#             */
/*   Updated: 2025/01/28 11:41:33 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	*add_scalar_local(t_vec3 *a, float scalar)
{
	a->x += scalar;
	a->y += scalar;
	a->z += scalar;
	return (a);
}

t_vec3	*sub_scalar_local(t_vec3 *a, float scalar)
{
	a->x -= scalar;
	a->y -= scalar;
	a->z -= scalar;
	return (a);
}

t_vec3	*mul_scalar_local(t_vec3 *a, float scalar)
{
	a->x *= scalar;
	a->y *= scalar;
	a->z *= scalar;
	return (a);
}

t_vec3	*div_scalar_local(t_vec3 *a, float scalar)
{
	a->x /= scalar;
	a->y /= scalar;
	a->z /= scalar;
	return (a);
}
