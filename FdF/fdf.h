/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:32:46 by jans              #+#    #+#             */
/*   Updated: 2024/10/24 20:58:00 by jans             ###   ########.fr       */
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
#define WIN_HEIGHT 800
#define WIN_WIDTH 1100

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	fdf(char	**map);
int		parse_map(char	***map, char *filename);
int		projected_x(t_point *p);
int		projected_y(t_point *p);
void	slope_less_then_one(t_point *a, t_point *b, t_data *img);
void	slope_bigger_than_one(t_point *a, t_point *b, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_wireframe(t_point ***points, t_data *img);
void	connect_vertical(t_point ***points, int x, int y, t_data *img);
void	connect_horizontal(t_point ***points, int x, int y, t_data *img);
void	draw_line(t_point p1, t_point p2, t_data *img, int z);
void	initialize(char **map, t_data *img);
t_point	***get_points_array(char **map);
t_point	**get_cols(char *line, int y, int len_y);

#endif
