/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:32:46 by jans              #+#    #+#             */
/*   Updated: 2024/10/22 21:51:31 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include "get_next_line.h"
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	draw_line(int *x_pos, int *y_pos, t_data *img, char axis);
void	fdf(char	**map);
void	convert_to_points(char **map);
int		parse_map(char	***map, char *filename);
int		*get_int_arr_line(char *line, int *len_x);
int		**to_int_array(char **map, int *len_x, int *len_y);
int		parse_map(char	***map, char *filename);

#endif
