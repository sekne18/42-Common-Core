/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:19:16 by jans              #+#    #+#             */
/*   Updated: 2024/10/21 09:51:41 by jsekne           ###   ########.fr       */
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
	if (!is_sorted(*stack_a))
		sort_3(stack_a);
}

void	sort_5(t_list **stack_a, t_list **stack_b, int len)
{
	int	l;

	l = len;
	while (len--)
	{
		if ((*stack_a)->index == 0 || (l == 5 && (*stack_a)->index == 1))
			pb(stack_a, stack_b, 0);
		else
			ra(stack_a, 0);
	}
	sort_3(stack_a);
	pa(stack_a, stack_b, 0);
	pa(stack_a, stack_b, 0);
	if ((*stack_a)->index > (*stack_a)->next->index)
		sa(stack_a, 0);
}