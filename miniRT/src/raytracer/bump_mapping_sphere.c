/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:26:07 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 09:38:48 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static inline float	calc_dhdu(t_txt_img *img, float u, float v)
{
	float	du;
	float	hl;
	float	hr;

	du = 0.001f;
	hl = sample_texture(img, fmaxf(u - du, 0), v).x;
	hr = sample_texture(img, u + du, v).x;
	return (-(hr - hl) * BUMP_STRENGTH);
}

static inline float	calc_dhdv(t_txt_img *img, float u, float v)
{
	float	dv;
	float	hd;
	float	hu;

	dv = 0.001f;
	hd = sample_texture(img, u, fmaxf(v - dv, 0)).x;
	hu = sample_texture(img, u, v + dv).x;
	return (-(hu - hd) * BUMP_STRENGTH);
}

void	adjust_texture_normal_sphere(t_hit_record *record, t_txt_img *bump_map)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	float	dhdu;
	float	dhdv;

	dhdu = calc_dhdu(bump_map, record->uv.x, record->uv.y);
	dhdv = calc_dhdv(bump_map, record->uv.x, record->uv.y);
	tangent = *normalize_local(&(t_vec3){{-record->point.y,
			record->point.x, 0.0f}});
	cross(&bitangent, &record->normal, &tangent);
	add_scaled_local(&record->normal, &tangent, dhdu);
	add_scaled_local(&record->normal, &bitangent, dhdv);
	normalize_local(&record->normal);
}

void	adjust_texture_normal(t_hit_record *record)
{
	t_txt_img		*img;

	if (!record->material->texture)
		return ;
	if (record->material->texture->type == T_BUMP)
		img = (t_txt_img *)record->material->texture->data;
	else if (record->material->texture->type == T_IMG_AND_BUMP)
		img = ((t_txt_img *)record->material->texture->data) + 1;
	else
		return ;
	if (record->type == SPHERE)
		adjust_texture_normal_sphere(record, img);
}
