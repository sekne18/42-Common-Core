/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:13:25 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 10:51:58 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

// flip v (up becomes down since y is inverted on screen)
static void	calc_viewport(t_camera *c, t_vec3 *direction, t_vec3 *up)
{
	t_viewport	*vp;

	vp = c->viewport;
	c->direction = *normalize_local(direction);
	vp->v = *normalize_local(up);
	vp->u = *normalize_local(cross_local(&vp->v, &c->direction));
	normalize_local(cross(&vp->v, &c->direction, &vp->u));
	vp->aspect_ratio = (float)c->width / (float)c->height;
	vp->delta_u = length(&vp->u) * tanf(c->hfov * 0.5f) * 2 / c->width;
	vp->delta_v = length(&vp->v) * tanf(c->hfov * 0.5f)
		* 2 / (c->height * vp->aspect_ratio);
	add_scaled(&vp->upper_left_corner, &c->origin, &c->direction, c->zoom);
	sub_scaled_local(&vp->upper_left_corner, &vp->u,
		tanf(c->hfov * 0.5f));
	add_scaled_local(&vp->upper_left_corner, &vp->v,
		tanf(c->hfov * 0.5f) / vp->aspect_ratio);
	mul_scalar_local(&vp->v, -1);
	add_scaled_local(&vp->upper_left_corner, &vp->u,
		vp->delta_u * 0.5f);
	add_scaled_local(&vp->upper_left_corner, &vp->v,
		vp->delta_v * 0.5f);
}

void	set_camera_orientation(t_camera *c, t_vec3 *direction)
{
	t_vec3		up;
	t_vec3		forward;
	t_vec3		axis;
	float		angle;

	c->direction = *normalize_local(direction);
	set_vector(&forward, 0, 0, -1);
	cross(&axis, &forward, &c->direction);
	angle = acosf(dot(&forward, &c->direction));
	if (angle < 0.000001 && angle > -0.000001)
		c->orientation = (t_quat){0, 0, 0, 1};
	else
		c->orientation = quat_from_axis_angle(&axis, angle);
	set_vector(&up, 0, 1, 0);
	up = rotate_vec(&up, &c->orientation);
	calc_viewport(c, direction, &up);
}

void	rotate_camera(t_camera *c, t_vec3 axis, float angle)
{
	t_quat	rotation;
	t_vec3	up;
	t_vec3	forward;

	normalize_local(&axis);
	rotation = quat_from_axis_angle(&axis, angle);
	c->orientation = mul_quat(&rotation, &c->orientation);
	normalize_quat(&c->orientation);
	set_vector(&up, 0, 1, 0);
	set_vector(&forward, 0, 0, -1);
	forward = rotate_vec(&forward, &c->orientation);
	up = rotate_vec(&up, &c->orientation);
	calc_viewport(c, &forward, &up);
}

void	adjust_camera_zoom(t_camera *c, float zoom)
{
	t_vec3	up;

	c->zoom = fmaxf(MIN_ZOOM, fminf(MAX_ZOOM, c->zoom + zoom));
	mul_scalar(&up, &c->viewport->v, -1);
	calc_viewport(c, &c->direction, &up);
}

void	translate_camera(t_camera *c, t_vec3 *translation)
{
	t_vec3	up;

	mul_scalar(&up, &c->viewport->v, -1);
	add_local(&c->origin, translation);
	calc_viewport(c, &c->direction, &up);
}
