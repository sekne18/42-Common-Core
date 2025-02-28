/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:49:33 by fmol              #+#    #+#             */
/*   Updated: 2025/02/18 12:13:14 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <stdlib.h>

typedef struct s_quat
{
	float	x;
	float	y;
	float	z;
	float	w;
}				t_quat;

typedef union s_vec3
{
	struct
	{
		float	x;
		float	y;
		float	z;
	};
	float		v[3];
}				t_vec3;

typedef struct s_vec2
{
	float	x;
	float	y;
}				t_vec2;

t_quat	quat_from_axis_angle(const t_vec3 *restrict axis, float angle);
t_quat	*normalize_quat(t_quat *q);
t_quat	mul_quat(const t_quat *restrict a, const t_quat *restrict b);
t_vec3	rotate_vec(const t_vec3 *restrict v, const t_quat *restrict q);

/*----------------------------------------- VECTORS --------------------------*/
/*for optimisation purposes, there are no validity checks inside the functions*/
/*							 make sure to use them correctly!				  */
/*----------------------------------------- VECTORS --------------------------*/

//prefer set_vector over new_vector because it does not have copy overhead
t_vec3	*set_vector(t_vec3 *restrict dest, float x, float y, float z);
t_vec3	*copy_vector(t_vec3 *restrict dest, const t_vec3 *restrict src);
t_vec3	new_vector(float x, float y, float z);
t_vec3	*create_vector(float x, float y, float z);

t_vec3	*add(t_vec3 *dest, const t_vec3 *restrict a, const t_vec3 *restrict b);
t_vec3	*sub(t_vec3 *dest, const t_vec3 *restrict a, const t_vec3 *restrict b);
t_vec3	*mul(t_vec3 *dest, const t_vec3 *restrict a, const t_vec3 *restrict b);
t_vec3	*div_vec(t_vec3 *dest, const t_vec3 *restrict a,
			const t_vec3 *restrict b);

t_vec3	*add_local(t_vec3 *a, const t_vec3 *restrict b);
t_vec3	*sub_local(t_vec3 *a, const t_vec3 *restrict b);
t_vec3	*mul_local(t_vec3 *a, const t_vec3 *restrict b);
t_vec3	*div_local(t_vec3 *a, const t_vec3 *restrict b);

t_vec3	*add_scalar(t_vec3 *dest, const t_vec3 *restrict a, float scalar);
t_vec3	*sub_scalar(t_vec3 *dest, const t_vec3 *restrict a, float scalar);
t_vec3	*mul_scalar(t_vec3 *dest, const t_vec3 *restrict a, float scalar);
t_vec3	*div_scalar(t_vec3 *dest, const t_vec3 *restrict a, float scalar);

t_vec3	*add_scalar_local(t_vec3 *a, float scalar);
t_vec3	*sub_scalar_local(t_vec3 *a, float scalar);
t_vec3	*mul_scalar_local(t_vec3 *a, float scalar);
t_vec3	*div_scalar_local(t_vec3 *a, float scalar);

t_vec3	*add_scaled_local(t_vec3 *a, const t_vec3 *restrict b, float scalar);
t_vec3	*sub_scaled_local(t_vec3 *a, const t_vec3 *restrict b, float scalar);
t_vec3	*mul_scaled_local(t_vec3 *a, const t_vec3 *restrict b, float scalar);
t_vec3	*div_scaled_local(t_vec3 *a, const t_vec3 *restrict b, float scalar);

t_vec3	*add_scaled(t_vec3 *dest, const t_vec3 *restrict a,
			const t_vec3 *restrict b, float scalar);
t_vec3	*sub_scaled(t_vec3 *dest, const t_vec3 *restrict a,
			const t_vec3 *restrict b, float scalar);
t_vec3	*sub_scaled_vec(t_vec3 *dest, const t_vec3 *restrict a,
			const t_vec3 *restrict b, const t_vec3 *restrict scalar);

void	min(t_vec3 *dest, const t_vec3 *restrict a, const t_vec3 *restrict b);
void	max(t_vec3 *dest, const t_vec3 *restrict a, const t_vec3 *restrict b);
void	min_local(t_vec3 *a, const t_vec3 *restrict b);
void	max_local(t_vec3 *a, const t_vec3 *restrict b);

float	length(const t_vec3 *restrict a);
float	length_squared(const t_vec3 *restrict a);
float	dot(const t_vec3 *restrict a, const t_vec3 *restrict b);
t_vec3	*cross(t_vec3 *dest, const t_vec3 *restrict a,
			const t_vec3 *restrict b);
t_vec3	*cross_local(t_vec3 *a, const t_vec3 *restrict b);

t_vec3	*normalize(t_vec3 *dest, const t_vec3 *restrict a);
t_vec3	*normalize_local(t_vec3 *a);

t_vec3	*add_copy(t_vec3 *restrict dest, const t_vec3 a);

#endif // VECTOR_H
