/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:46:36 by jans              #+#    #+#             */
/*   Updated: 2024/11/09 11:50:11 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	merge_sort_small(t_list **stack_a, t_list **stack_b)
{
	int	median;
	int	size;

	size = ft_lstsize(*stack_a);
	if (size > 3)
	{
		median = find_median(*stack_a, size);
		while (size--)
		{
			if ((*stack_a)->index < median)
				pb(stack_a, stack_b, 0);
			else
			{
				if (ft_lstsize(*stack_a) > 1)
					ra(stack_a, 0);
			}
		}
		merge_sort_small(stack_a, stack_b);
	}
	else if (size == 3)
		sort_3(stack_a);
	else if (size == 2 && !is_sorted(*stack_a))
		sa(stack_a, 0);
	move_to_stack_aa(stack_a, stack_b);
}

void	merge_sort_big(t_list **stack_a, t_list **stack_b)
{
	int	q1;
	int	q2;
	int	q3;

	find_quartiles(*stack_a, &q1, &q2, &q3);
	push_quartile_to_b(stack_a, stack_b, q1, 0);
	push_quartile_to_b(stack_a, stack_b, q2, q1);
	push_quartile_to_b(stack_a, stack_b, q3, q2);
	push_quartile_to_b(stack_a, stack_b, INT_MAX, q3);
	move_to_stack_aa(stack_a, stack_b);
}

void	push_quartile_to_b(t_list **stack_a, t_list **stack_b, int upper_bound,
		int lower_bound)
{
	int	size;

	size = ft_lstsize(*stack_a);
	while (size--)
	{
		if ((*stack_a)->index >= lower_bound && (*stack_a)->index < upper_bound)
		{
			pb(stack_a, stack_b, 0);
			if ((*stack_b)->next && (*stack_b)->index < (*stack_b)->next->index)
				rb(stack_b, 0);
		}
		else
			ra(stack_a, 0);
	}
}

void	move_to_stack_aa(t_list **stack_a, t_list **stack_b)
{
	int	max;
	int	size;
	int	steps_to_rot;

	if (!*stack_b)
		return ;
	size = ft_lstsize(*stack_b);
	max = ft_lstmax_idx(*stack_b);
	steps_to_rot = rotate_count(*stack_b, max);
	if (steps_to_rot > size / 2)
		rot_to_pos(size - steps_to_rot, stack_b, &rrb);
	else
		rot_to_pos(steps_to_rot, stack_b, &rb);
	pa(stack_a, stack_b, 0);
	move_to_stack_aa(stack_a, stack_b);
}
