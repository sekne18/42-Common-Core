/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:50:00 by jans              #+#    #+#             */
/*   Updated: 2024/10/18 18:07:12 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%d", lst->number);
		if (lst->next)
			printf(" -> ");
		lst = lst->next;
	}
	printf("\n");
}

int	ft_lstmax_idx(t_list *stack)
{
	int	max;

	if (!stack)
		return (0);
	max = stack->index;
	while (stack->next)
	{
		if (max < stack->index)
			max = stack->index;
		stack = stack->next;
	}
	return (max);
}

int	ft_lstmin(t_list *stack)
{
	int	min;

	if (!stack)
		return (0);
	min = stack->number;
	while (stack->next)
	{
		if (min > stack->number)
			min = stack->number;
		stack = stack->next;
	}
	return (min);
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

int	is_sorted(t_list *stack)
{
	t_list	*curr;

	curr = stack;
	while (curr->next)
	{
		if (curr->index < curr->next->index)
			return (0);
		curr = curr->next;
	}
	return (1);
}
