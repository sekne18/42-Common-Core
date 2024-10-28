/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:32:46 by jans              #+#    #+#             */
/*   Updated: 2024/10/28 19:15:39 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include "./mlx/mlx.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# define WIN_WIDTH 1620
# define WIN_HEIGHT 950

# ifdef __APPLE__
#  define ESCAPE 53
# else
#  define ESCAPE 65307
# endif

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_data		*data;
	t_point		***points;
	int			min_z;
	int			max_z;
}				t_vars;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

void			fdf(char **map);
int				parse_map(char ***map, char *filename);
int				projected_x(t_point *p, int scale);
int				projected_y(t_point *p, int scale);
int				ft_close_win(void *param);
int				ft_key_press(int keycode, void *param);
void			set_setters(t_point a, t_point b, int *sy, int *sx);
void			check_if_square(t_point ***points, char **map, t_vars *vars);
void			get_lines(int fd, char **line);
void			cleanup(t_vars *vars);
void			free_points(t_point ***points);
void			slope_less_then_one(t_point *a, t_point *b, t_vars *vars,
					int z);
void			slope_bigger_than_one(t_point *a, t_point *b, t_vars *vars,
					int z);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			draw_wireframe(t_point ***points, t_vars *vars);
void			connect_vertical(t_point ***points, int x, int y, t_vars *vars);
void			connect_horizontal(t_point ***points, int x, int y,
					t_vars *vars);
void			init_mlx(t_vars *vars);
void			set_z_limits(t_point ***points, t_vars *vars);
int				init_vars(t_vars **vars);
int				ft_draw(t_vars *vars);
void			ft_hook_init(t_vars *vars);
t_point			***get_points_array(char **map, t_vars *vars);
t_point			**get_cols(char *line, int y, int len_y);
unsigned int	interpolate_color(int min_z, int max_z, int z);

#endif
