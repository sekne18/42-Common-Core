/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:59:39 by jsekne            #+#    #+#             */
/*   Updated: 2024/11/25 14:57:01 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_point	*ft_new_point(int x, int y, int z)
{
	t_point	*node;

	node = malloc(sizeof(t_point));
	if (!node)
		return (NULL);
	node->y = y;
	node->x = x;
	node->z = z;
	return (node);
}

t_info	*ft_new_info(int cols, int rows)
{
	t_info	*node;

	node = malloc(sizeof(t_info));
	if (!node)
		return (NULL);
	node->cols = cols;
	node->rows = rows;
	return (node);
}
