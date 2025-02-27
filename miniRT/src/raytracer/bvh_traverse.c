/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_traverse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 13:21:01 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 12:55:12 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static inline void	hit_faces(t_ray *ray, t_hit_record *record,
	t_object *obj, t_bvh_node *current)
{
	float			t;
	unsigned int	i;

	i = 0;
	while (i < current->primitive_count)
	{
		t = hit_face(ray, ((t_mesh *)obj->data)->faces + current->primitives[i],
				((t_mesh *)obj->data)->vertices,
				((t_mesh *)obj->data)->face_edges + current->primitives[i] * 2);
		if (t > 0.0 && t < record->t)
		{
			fill_face_record(record, ray, t);
			set_face_normal(record, obj->data,
				&(unsigned int){current->primitives[i]});
			record->material = obj->material;
		}
		i++;
	}
}

void	intersect_mesh_bvh(t_ray *ray, t_scene *scene,
	t_hit_record *record, unsigned int mesh_i)
{
	t_mesh_bvh		*mesh_bvh;
	t_bvh_node		*current;
	float			t1;
	float			t2;
	unsigned int	old_stack_ptr;

	mesh_bvh = scene->bvh->mesh_bvhs + mesh_i;
	old_stack_ptr = scene->bvh->stack_ptr;
	scene->bvh->stack[scene->bvh->stack_ptr++] = 0;
	while (scene->bvh->stack_ptr > old_stack_ptr)
	{
		current = mesh_bvh->nodes + scene->bvh->stack[--scene->bvh->stack_ptr];
		if (current->left == 0)
			hit_faces(ray, record, (scene->objects + mesh_i), current);
		else
		{
			t1 = hit_bbox(ray, &mesh_bvh->nodes[current->left].bbox);
			t2 = hit_bbox(ray, &mesh_bvh->nodes[current->right].bbox);
			if (t1 > 0.0 && t1 < record->t)
				scene->bvh->stack[scene->bvh->stack_ptr++] = current->left;
			if (t2 > 0.0 && t2 < record->t)
				scene->bvh->stack[scene->bvh->stack_ptr++] = current->right;
		}
	}
}

static inline void	add_next_visit_bvh(t_bvh *bvh, t_bvh_node *curr,
	t_ray *ray, t_hit_record *record)
{
	float	t1;
	float	t2;

	t1 = hit_bbox(ray, &bvh->nodes[curr->left].bbox);
	t2 = hit_bbox(ray, &bvh->nodes[curr->right].bbox);
	if (t1 > 0.0 && t1 < record->t)
		bvh->stack[bvh->stack_ptr++] = curr->left;
	if (t2 > 0.0 && t2 < record->t)
		bvh->stack[bvh->stack_ptr++] = curr->right;
}

static inline void	hit_primitives(t_ray *ray, t_scene *scene,
	t_hit_record *record, t_bvh_node *current)
{
	float			t;
	unsigned int	i;

	i = 0;
	while (i < current->primitive_count)
	{
		t = check_hit(ray, scene->objects + current->primitives[i]);
		if (t > 0.0 && t < record->t)
		{
			if (scene->objects[current->primitives[i]].type == MESH)
				intersect_mesh_bvh(ray, scene,
					record, current->primitives[i]);
			else
				fill_record(record, ray,
					scene->objects + current->primitives[i], t);
		}
		i++;
	}
}

void	intersect_bvh(t_ray *ray, t_scene *scene, t_hit_record *record)
{
	t_bvh_node		*current;

	scene->bvh->stack_ptr = 0;
	scene->bvh->stack[scene->bvh->stack_ptr++] = 0;
	while (scene->bvh->stack_ptr > 0)
	{
		current = scene->bvh->nodes
			+ scene->bvh->stack[--scene->bvh->stack_ptr];
		if (current->left == 0)
			hit_primitives(ray, scene, record, current);
		else
			add_next_visit_bvh(scene->bvh, current, ray, record);
	}
}
