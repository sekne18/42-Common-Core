/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:59:39 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/22 21:38:17 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_point	*ft_lstnew(int x, int y, int z)
{
	t_point	*node;

	node = malloc(sizeof(t_point));
	if (!node)
		return (NULL);
	node->y = y;
	node->x = x;
	node->z = z;
	node->next = NULL;
	return (node);
}
