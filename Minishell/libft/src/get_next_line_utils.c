/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 10:25:38 by fmol              #+#    #+#             */
/*   Updated: 2024/10/23 11:11:06 by fmol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_lnode	*lstfind_fd(t_lnode *start, int fd)
{
	if (!start)
		return (NULL);
	else if (start->fd == fd)
		return (start);
	return (lstfind_fd(start->next, fd));
}

t_lnode	*lstadd_fd(t_lnode **start, int fd)
{
	t_lnode	*new;
	t_lnode	*tmp;

	new = malloc(sizeof(t_lnode));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->line = malloc(sizeof(char) * 1);
	if (!new->line)
		return (NULL);
	new->line[0] = '\0';
	new->next = NULL;
	if (!(*start))
		*start = new;
	else
	{
		tmp = *start;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

int	lstremove_fd(t_lnode **start, int fd)
{
	t_lnode	*tmp;
	t_lnode	*prev;

	if (!(*start))
		return (0);
	prev = NULL;
	tmp = *start;
	while (tmp)
	{
		if (tmp->fd == fd)
		{
			free(tmp->line);
			if (!prev)
				*start = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp);
			return (1);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}
