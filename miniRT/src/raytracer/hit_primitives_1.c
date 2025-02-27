/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_primitives_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:03:18 by fmol              #+#    #+#             */
/*   Updated: 2025/02/18 13:49:40 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

//last conditional (t < 0.0): for rendering sphere when you are inside 
// + for refraction when light leaving sphere
float	hit_sphere(t_ray *ray, t_sphere *sphere)
{
	t_vec3	oc;
	float	a;
	float	h;
	float	discriminant;
	float	t;

	sub(&oc, &sphere->center, &ray->origin);
	a = length_squared(&ray->direction);
	h = dot(&oc, &ray->direction);
	discriminant = h * h - a
		* (length_squared(&oc) - sphere->radius * sphere->radius);
	if (discriminant < 0.0)
		return (-1.0);
	t = (h - sqrt(discriminant)) / a;
	if (t < 0.0)
		t = (h + sqrt(discriminant)) / a;
	return (t);
}

float	hit_plane(t_ray *ray, t_plane *plane)
{
	float	denom;
	float	t;

	denom = dot(&plane->normal, &ray->direction);
	if (denom > -0.000001 && denom < 0.000001)
		return (-1.0);
	t = (dot(&plane->normal, &plane->point)
			- dot(&plane->normal, &ray->origin)) / denom;
	if (t < 0.0)
		return (-1.0);
	return (t);
}

float	hit_quad(t_ray *ray, t_quad *quad)
{
	float	t;
	t_vec3	intersect;
	t_vec3	tmp;
	float	alpha;
	float	beta;

	t = hit_plane(ray, &(t_plane){quad->normal, quad->point});
	if (t < 0.0)
		return (-1.0);
	ray_at(&intersect, ray, t);
	sub_local(&intersect, &quad->point);
	cross(&tmp, &intersect, &quad->v);
	alpha = dot(&quad->w, &tmp);
	cross(&tmp, &quad->u, &intersect);
	beta = dot(&quad->w, &tmp);
	if (alpha < 0.0 || alpha > 1.0 || beta < 0.0 || beta > 1.0)
		return (-1.0);
	return (t);
}

float	hit_disk(t_ray *ray, t_disk *disk)
{
	t_vec3	oc;
	t_vec3	point;
	float	denom;
	float	t;

	denom = dot(&disk->normal, &ray->direction);
	if (denom > -0.000001 && denom < 0.000001)
		return (-1.0);
	t = dot(&disk->normal, &disk->center) - dot(&disk->normal, &ray->origin);
	t /= denom;
	if (t < 0.0)
		return (-1.0);
	ray_at(&point, ray, t);
	sub(&oc, &point, &disk->center);
	if (length_squared(&oc) > disk->radius * disk->radius)
		return (-1.0);
	return (t);
}

//moller-trumbore algorithm
float	hit_triangle(t_ray *ray, t_triangle *triangle)
{
	t_vec3	tmp1;
	t_vec3	tmp2;
	float	det;
	float	u;
	float	v;

	cross(&tmp1, &ray->direction, &triangle->edge2);
	det = dot(&triangle->edge1, &tmp1);
	if (det > -0.000001 && det < 0.000001)
		return (-1.0);
	det = 1.0 / det;
	sub(&tmp2, &ray->origin, &triangle->vertices[0]);
	u = dot(&tmp2, &tmp1) * det;
	if (u < 0.0 || u > 1.0)
		return (-1.0);
	cross(&tmp1, &tmp2, &triangle->edge1);
	v = dot(&ray->direction, &tmp1) * det;
	if (v < 0.0 || u + v > 1.0)
		return (-1.0);
	u = dot(&triangle->edge2, &tmp1) * det;
	if (u > 0.000001)
		return (u);
	return (-1.0);
}
