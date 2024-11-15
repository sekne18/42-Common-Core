/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:46:36 by jans              #+#    #+#             */
/*   Updated: 2024/11/15 16:01:56 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	merge_sort_small(t_list **stack_a, t_list **stack_b)
{
	int	median;
	int	size;
	int steps_to_rot_a;
	int	to_move;

	size = ft_lstsize(*stack_a);
	if (size == 2)
		sa(stack_a, 0);
	else if (size == 3)
		sort_3(stack_a);
	else if (size < 6)
		sort_5(stack_a, stack_b, size);
	else if (size > 5)
	{
		median = find_median(*stack_a, size);
		to_move = size/2;	
		while (to_move)
		{
			steps_to_rot_a = rotate_count_median(*stack_a, median);
			if (steps_to_rot_a > size / 2)
				rot_to_pos_a(size - steps_to_rot_a, stack_a, &rra);
			else
				rot_to_pos_a(steps_to_rot_a, stack_a, &ra);
			if ((*stack_a)->index < median)
			{
				pb(stack_a, stack_b, 0);
				to_move--;
			}
		}
		merge_sort_small(stack_a, stack_b);
	}
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
	push_quartile_to_b(stack_a, stack_b, ft_lstmax_idx(*stack_a), q3);
	move_to_stack_aa(stack_a, stack_b);
}

void	push_quartile_to_b(t_list **stack_a, t_list **stack_b, int upper_bound,
		int lower_bound)
{
	int	size;
	int	to_move;
	int	steps_to_rot_a;

	size = ft_lstsize(*stack_a);
	to_move = upper_bound - lower_bound; // not sure here!
	while (to_move)
	{
		steps_to_rot_a = rotate_count_quartile(*stack_a, upper_bound, lower_bound);
		if (steps_to_rot_a > size / 2)
			rot_to_pos_a(size - steps_to_rot_a, stack_a, &rra);
		else
			rot_to_pos_a(steps_to_rot_a, stack_a, &ra);	
		if ((*stack_a)->index >= lower_bound && (*stack_a)->index < upper_bound)
		{
			pb(stack_a, stack_b, 0);
			to_move--;
		}
		/*if ((*stack_a)->index >= lower_bound && (*stack_a)->index < upper_bound)
		{
			pb(stack_a, stack_b, 0);
			if ((*stack_b)->next && (*stack_b)->index < (*stack_b)->next->index)
				rb(stack_b, 0);
		}
		else
			ra(stack_a, 0);*/
	}
}

void	move_to_stack_aa(t_list **stack_a, t_list **stack_b)
{
	if (!*stack_b)
		return ;
	rot_to_pos_b(stack_a, stack_b);
	pa(stack_a, stack_b, 0);
	if ((*stack_a)->index > (*stack_a)->next->index)
		sa(stack_a, 0);
	move_to_stack_aa(stack_a, stack_b);
}
