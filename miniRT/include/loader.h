/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <fmol@student.s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:16:56 by fmol              #+#    #+#             */
/*   Updated: 2025/02/18 15:02:24 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADER_H
# define LOADER_H

# include "scene.h"
# include <stdio.h>
# define MAX_LINE_LENGTH 8192

t_mesh			*load_obj(char *filename);
t_texture		*create_checkerboard_texture(t_vec3 *color1, t_vec3 *color2);
t_texture		*create_img_texture(char *filename);
t_texture		*create_img_bump_texture(char *filename, char *bump_filename);
t_texture		*create_bump_texture(char *filename);
unsigned char	*load_ppm(char *filename, int *width, int *height);
void			destroy_texture(t_texture *texture);
#endif // LOADER_H
