/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:52:37 by fmol              #+#    #+#             */
/*   Updated: 2025/02/12 10:53:33 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LERP_H
# define LERP_H

# include "vector.h"

t_vec3	lerp_vec(const t_vec3 *a, const t_vec3 *b, float t);
float	lerp_float(float a, float b, float t);
t_vec3	lerp_vec_multiple(const t_vec3 *list, size_t size, float t);

#endif