/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 23:32:46 by jans              #+#    #+#             */
/*   Updated: 2024/10/22 14:16:28 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int		parse_map(char	***map, char *filename);
void	fdf(char	**map);
int		*get_int_arr_line(char *line, int *len_x);
int		**to_int_array(char **map, int *len_x, int *len_y);

#endif
