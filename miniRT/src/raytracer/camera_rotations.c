/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:37:45 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 10:42:29 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void	rotate_camera_yaw(t_camera *c, float angle)
{
	t_vec3	axis;

	mul_scalar(&axis, &c->viewport->v, -1);
	rotate_camera(c, axis, angle);
}

void	rotate_camera_pitch(t_camera *c, float angle)
{
	t_vec3	axis;

	copy_vector(&axis, &c->viewport->u);
	rotate_camera(c, axis, angle);
}

void	rotate_camera_roll(t_camera *c, float angle)
{
	t_vec3	axis;

	copy_vector(&axis, &c->direction);
	rotate_camera(c, axis, angle);
}
