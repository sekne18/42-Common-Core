/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:58:35 by fmol              #+#    #+#             */
/*   Updated: 2025/02/18 15:15:05 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static inline void	add_bbox_color(t_vec3 *color, int type, float scale)
{
	t_vec3	tmp;

	if (type == 0)
		set_vector(&tmp, COLOR_BVH_R, COLOR_BVH_G, COLOR_BVH_B);
	else
		set_vector(&tmp, COLOR_BVH_MESH_R, COLOR_BVH_MESH_G, COLOR_BVH_MESH_B);
	add_scaled_local(color, &tmp, scale);
}

static inline t_vec3	trace_mesh_bvh(t_ray *ray, t_mesh_bvh *bvh,
	unsigned int *stack, unsigned int stack_offset)
{
	t_vec3			color;
	t_bvh_node		*current;
	float			scale;
	unsigned int	stack_ptr;
	float			t;

	scale = 1 / ((float)calc_mesh_depth(bvh, 0, 0));
	set_vector(&color, 0.0, 0.0, 0.0);
	stack_ptr = 0;
	stack[stack_offset + stack_ptr++] = 0;
	while (stack_ptr != 0)
	{
		current = bvh->nodes + stack[stack_offset + --stack_ptr];
		t = hit_bbox(ray, &current->bbox);
		if (t > 0.0 && t < INFINITY)
		{
			add_bbox_color(&color, 1, scale);
			if (current->left != 0)
			{
				stack[stack_offset + stack_ptr++] = current->left;
				stack[stack_offset + stack_ptr++] = current->right;
			}
		}
	}
	return (color);
}

static inline t_vec3	get_bbox_color(t_bvh_node *current, t_ray *ray,
	t_scene *scene, t_bvh *bvh)
{
	t_vec3			color;
	t_vec3			tmp;
	unsigned int	i;
	float			t;

	set_vector(&color, 0.0, 0.0, 0.0);
	i = 0;
	if (current->left != 0)
		return (color);
	while (i < current->primitive_count)
	{
		if (scene->objects[current->primitives[i]].type == MESH)
		{
			t = hit_bbox(ray, &scene->objects[current->primitives[i]].bbox);
			if (t > 0.0 && t < INFINITY)
			{
				tmp = trace_mesh_bvh(ray, bvh->mesh_bvhs
						+ current->primitives[i],
						bvh->stack, bvh->stack_ptr);
				add_local(&color, &tmp);
			}
		}
		i++;
	}
	return (color);
}

t_vec3	trace_bvh(t_ray *ray, t_bvh *bvh, t_scene *scene)
{
	t_vec3			color;
	t_bvh_node		*current;
	float			scale;
	float			t;

	set_vector(&color, 0.0, 0.0, 0.0);
	scale = 1 / ((float)calc_depth(bvh, 0, 0));
	bvh->stack_ptr = 0;
	bvh->stack[bvh->stack_ptr++] = 0;
	while (bvh->stack_ptr != 0)
	{
		current = bvh->nodes + bvh->stack[--bvh->stack_ptr];
		t = hit_bbox(ray, &current->bbox);
		if (t > 0.0 && t < INFINITY)
		{
			add_copy(&color, get_bbox_color(current, ray, scene, bvh));
			add_bbox_color(&color, 0, scale);
			if (current->left != 0)
			{
				bvh->stack[bvh->stack_ptr++] = current->left;
				bvh->stack[bvh->stack_ptr++] = current->right;
			}
		}
	}
	return (color);
}
