/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:46:36 by jans              #+#    #+#             */
/*   Updated: 2024/11/19 11:32:56 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	merge_sort(t_list **stack_a, t_list **stack_b)
{
	int	q1;
	int	q2;
	int	q3;

	find_quartiles(*stack_a, &q1, &q2, &q3);
	push_quartile_to_b(stack_a, stack_b, q1, 0);
	push_quartile_to_b(stack_a, stack_b, q2, q1);
	push_quartile_to_b(stack_a, stack_b, q3, q2);
	push_quartile_to_b(stack_a, stack_b, ft_lstmax_idx(*stack_a), q3);
	move_to_stack_a(stack_a, stack_b);
}

void	push_quartile_to_b(t_list **stack_a, t_list **stack_b, int upper_bound,
		int lower_bound)
{
	int	size;
	int	to_move;
	int	steps_to_rot_a;

	size = ft_lstsize(*stack_a);
	to_move = upper_bound - lower_bound;
	while (to_move)
	{
		steps_to_rot_a = rotate_count_quartile(*stack_a, upper_bound,
				lower_bound);
		if (steps_to_rot_a > size / 2)
			rot_to_pos_a(size - steps_to_rot_a, stack_a, &rra);
		else
			rot_to_pos_a(steps_to_rot_a, stack_a, &ra);
		if ((*stack_a)->index >= lower_bound && (*stack_a)->index < upper_bound)
		{
			pb(stack_a, stack_b, 0);
			to_move--;
		}
	}
}

void	move_to_stack_a(t_list **stack_a, t_list **stack_b)
{
	if (!*stack_b)
		return ;
	rot_to_pos_b(stack_a, stack_b);
	pa(stack_a, stack_b, 0);
	if ((*stack_a)->index > (*stack_a)->next->index)
		sa(stack_a, 0);
	move_to_stack_a(stack_a, stack_b);
}
