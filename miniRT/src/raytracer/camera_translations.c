/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_translations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:37:50 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 10:51:20 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void	translate_camera_forward(t_camera *c, float distance)
{
	t_vec3	translation;

	mul_scalar(&translation, &c->direction, distance);
	translate_camera(c, &translation);
}

void	translate_camera_up(t_camera *c, float distance)
{
	t_vec3	translation;

	mul_scalar(&translation, &c->viewport->v, -distance);
	translate_camera(c, &translation);
}

void	translate_camera_right(t_camera *c, float distance)
{
	t_vec3	translation;

	mul_scalar(&translation, &c->viewport->u, distance);
	translate_camera(c, &translation);
}
