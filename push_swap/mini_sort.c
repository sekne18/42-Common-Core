/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:19:16 by jans              #+#    #+#             */
/*   Updated: 2024/11/19 11:57:37 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	mini_sort(t_list **stack_a, t_list **stack_b, int len)
{
	if (len == 3)
		sort_3(stack_a);
	else if (len <= 5)
		sort_5(stack_a, stack_b, len);
}

void	sort_3(t_list **stack_a)
{
	t_list	*head;

	head = *stack_a;
	if (head->number > head->next->number)
	{
		if (head->number > head->next->next->number)
			rra(stack_a, 0);
		else
			sa(stack_a, 0);
	}
	else
		rra(stack_a, 0);
	if (!is_sorted(*stack_a, 1))
		sort_3(stack_a);
}

void	sort_5(t_list **stack_a, t_list **stack_b, int len)
{
	int	l;
	int	min;
	int	push_count;

	push_count = 0;
	l = len;
	min = ft_lstmin(*stack_a);
	while (len--)
	{
		if ((*stack_a)->index == min
			|| (l == 5 && (*stack_a)->index == (min + 1)))
		{
			pb(stack_a, stack_b, 0);
			push_count++;
		}
		else
			ra(stack_a, 0);
	}
	sort_3(stack_a);
	while (push_count--)
		pa(stack_a, stack_b, 0);
	if ((*stack_a)->index > (*stack_a)->next->index)
		sa(stack_a, 0);
}
