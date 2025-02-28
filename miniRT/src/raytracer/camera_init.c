/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:48:23 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 10:52:13 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

int	init_camera(t_context *context, t_vec3 origin, t_vec3 direction, float hfov)
{
	t_camera	*res;
	t_viewport	*vp;

	res = malloc(sizeof(t_camera));
	vp = ft_calloc(1, sizeof(t_viewport));
	if (!res || !vp)
		return (free(res), free(vp), 0);
	res->origin = origin;
	res->direction = direction;
	res->orientation = (t_quat){0, 0, 0, 1};
	res->hfov = hfov;
	res->zoom = 1.0;
	res->width = context->width;
	res->height = context->height;
	res->viewport = vp;
	set_camera_orientation(res, &direction);
	context->camera = res;
	return (1);
}

void	cleanup_camera(t_camera *camera)
{
	if (!camera)
		return ;
	if (camera->viewport)
		free(camera->viewport);
	free(camera);
}
