/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:51:37 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 10:59:43 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

t_vec3	sample_texture(t_txt_img *img, float u, float v)
{
	int		index;
	int		x;
	int		y;

	x = (int)(u * img->width) % img->width;
	y = (int)(v * img->height) % img->height;
	index = (y * img->width + x) * 3;
	return ((t_vec3){{((t_txt_img *)img)->data[index] * INV_COLOR,
			((t_txt_img *)img)->data[index + 1] * INV_COLOR,
			((t_txt_img *)img)->data[index + 2] * INV_COLOR}});
}

t_vec3	get_texture_color(t_material *mtl, t_vec2 *uv, t_vec3 *point,
	t_object_type type)
{
	(void)point;
	if (!mtl->texture)
		return (mtl->diffuse);
	if (mtl->texture->type == T_CHECKERBOARD && type == SPHERE)
	{
		if ((int)(uv->x * 10) % 2 == (int)(uv->y * 10) % 2)
			return (((t_vec3 *)mtl->texture->data)[0]);
		return (((t_vec3 *)mtl->texture->data)[1]);
	}
	else if (mtl->texture->type == T_IMAGE && type == SPHERE)
		return (sample_texture(mtl->texture->data, uv->x, uv->y));
	else if (mtl->texture->type == T_IMG_AND_BUMP && type == SPHERE)
		return (sample_texture(mtl->texture->data, uv->x, uv->y));
	return (mtl->diffuse);
}
