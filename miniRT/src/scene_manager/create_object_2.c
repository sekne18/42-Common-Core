/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:34:03 by fmol              #+#    #+#             */
/*   Updated: 2025/02/17 16:39:37 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_object	create_triangle(t_vec3 vertices[3])
{
	t_triangle	*triangle;
	t_vec3		center;
	t_vec3		normal;
	t_vec3		edge1;
	t_vec3		edge2;

	triangle = malloc(sizeof(t_triangle));
	if (!triangle)
		return ((t_object){0});
	add(&center, &vertices[0], &vertices[1]);
	add_local(&center, &vertices[2]);
	div_scalar_local(&center, 3);
	sub(&edge1, &vertices[1], &vertices[0]);
	sub(&edge2, &vertices[2], &vertices[0]);
	cross(&normal, &edge1, &edge2);
	normalize_local(&normal);
	ft_memcpy(triangle, &(t_triangle){{vertices[0], vertices[1],
		vertices[2]}, edge1, edge2, normal}, sizeof(t_triangle));
	return ((t_object){NULL, TRIANGLE, get_triangle_aabb(triangle),
		center, triangle});
}
