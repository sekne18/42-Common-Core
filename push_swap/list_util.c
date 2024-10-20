/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:50:00 by jans              #+#    #+#             */
/*   Updated: 2024/10/20 15:23:23 by jans             ###   ########.fr       */
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
		if (min->number > stack->number)
			min = stack;
		stack = stack->next;
	}
	return (min->number);
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
		if (curr->number > curr->next->number)
			return (0);
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
