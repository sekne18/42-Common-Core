/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_children_mesh_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:57:22 by jsekne            #+#    #+#             */
/*   Updated: 2025/02/19 10:03:45 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	init_values(t_aabb *left_bbox, t_aabb *right_bbox,
		unsigned int *left_count, unsigned int *right_count)
{
	*left_count = 0;
	*right_count = 0;
	*left_bbox = ((t_aabb){{{1e30f, 1e30f, 1e30f}}, {{-1e30f, -1e30f,
			-1e30f}}});
	*right_bbox = ((t_aabb){{{1e30f, 1e30f, 1e30f}}, {{-1e30f, -1e30f,
			-1e30f}}});
}
