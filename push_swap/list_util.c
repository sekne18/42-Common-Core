/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:50:00 by jans              #+#    #+#             */
/*   Updated: 2024/11/19 14:52:27 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	ft_lstmax_idx(t_list *stack)
{
	int	max;

	if (!stack)
		return (0);
	max = stack->index;
	while (stack)
	{
		if (max < stack->index)
			max = stack->index;
		stack = stack->next;
	}
	return (max);
}

int	ft_lstmin(t_list *stack)
{
	t_list	*min;

	if (!stack)
		return (0);
	min = stack;
	while (stack)
	{
		if (min->index > stack->index)
			min = stack;
		stack = stack->next;
	}
	return (min->index);
}

int	ft_lstlast_idx(t_list *stack)
{
	int	last;

	if (!stack)
		return (0);
	while (stack->next)
		stack = stack->next;
	last = stack->index;
	return (last);
}

int	is_sorted(t_list *stack, int desc)
{
	t_list	*curr;

	if (!stack)
		return (1);
	curr = stack;
	while (curr->next)
	{
		if (desc)
		{
			if (curr->number > curr->next->number)
				return (0);
		}
		else
		{
			if (curr->number < curr->next->number || is_too_big_gap(curr->index,
					curr->next->index))
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}

int	ft_lst_nextmin(t_list *stack)
{
	t_list	*min;
	t_list	*curr;

	curr = stack;
	min = NULL;
	while (curr)
	{
		if (curr->index == -1 && (!min || min->number > curr->number))
			min = curr;
		curr = curr->next;
	}
	return (min->number);
}
