/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:27:16 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 16:04:03 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "vector.h"

# define MAX_PRIMITIVES 2
# define BBOX_PADDING 0.0001

typedef struct s_aabb
{
	t_vec3	min;
	t_vec3	max;
}			t_aabb;

typedef struct s_bvh_node
{
	t_aabb				bbox;
	unsigned int		left;
	unsigned int		right;
	unsigned int		*primitives;
	unsigned int		primitive_count;
}				t_bvh_node;

typedef struct s_mesh_bvh
{
	t_bvh_node		*nodes;
	t_vec3			*centers;
	t_aabb			*bboxes;
	unsigned int	node_count;
}				t_mesh_bvh;

// stack is used to keep track of the nodes that need to be traversed
// is used for both the bvh and mesh_bvh traversal
// (mesh_bvh traversal is done on top of bvh traversal in the stack)
typedef struct s_bvh
{
	t_bvh_node		*nodes;
	t_mesh_bvh		*mesh_bvhs;
	unsigned int	mesh_count;
	unsigned int	node_count;
	unsigned int	*stack;
	unsigned int	stack_ptr;
	unsigned int	stack_size;
	//unsigned int root; = always 0
}				t_bvh;

float			surface_area(t_aabb *bbox);
void			pad(t_aabb *bbox, float padding);

void			grow_to_include_point(t_aabb *bbox, t_vec3 *point);
void			grow_to_include_bbox(t_aabb *bbox, t_aabb *c1);
void			grow_to_include_face(t_aabb *bbox,
					t_vec3 *vertices, unsigned int *indices);
unsigned int	calc_depth(t_bvh *bvh, unsigned int node, unsigned int depth);
unsigned int	calc_max_mesh_depth(t_bvh *bvh);
unsigned int	largest_node_count_meshes(t_bvh *bvh);
unsigned int	calc_mesh_depth(t_mesh_bvh *bvh,
					unsigned int node, unsigned int depth);

void			cleanup_bvh(t_bvh *bvh);
void			cleanup_mesh_bvh(t_mesh_bvh *mesh_bvh);

#endif // BVH_H