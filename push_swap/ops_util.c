/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:17:11 by jans              #+#    #+#             */
/*   Updated: 2024/11/19 15:13:33 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	perform_rotation_and_move(t_list **stack_a, t_list **stack_b, int count,
		int reverse)
{
	int	can_move;

	can_move = 1;
	while (count--)
	{
		if (reverse)
		{
			if (next_to_be_moved(*stack_b) && can_move)
			{
				pa(stack_a, stack_b, 0);
				can_move--;
			}
			rrb(stack_b, 0);
		}
		else
		{
			if (next_to_be_moved(*stack_b) && can_move)
			{
				pa(stack_a, stack_b, 0);
				can_move--;
			}
			else
				rb(stack_b, 0);
		}
	}
}

void	rot_to_pos_b(t_list **stack_a, t_list **stack_b)
{
	int	size;
	int	max;
	int	steps_to_rot;
	int	count;

	size = ft_lstsize(*stack_b);
	max = ft_lstmax_idx(*stack_b);
	steps_to_rot = rotate_count(*stack_b, max);
	if (steps_to_rot > size / 2)
	{
		count = size - steps_to_rot;
		perform_rotation_and_move(stack_a, stack_b, count, 1);
	}
	else
	{
		count = steps_to_rot;
		perform_rotation_and_move(stack_a, stack_b, count, 0);
	}
}

void	rot_to_pos_a(int count, t_list **stack, void (*op)(t_list **stack_b,
			int bonus))
{
	while (count--)
	{
		op(stack, 0);
	}
}

int	rotate_count_quartile(t_list *stack, int upper_bound, int lower_bound)
{
	int	steps;

	steps = 0;
	while (stack)
	{
		if (stack->index < upper_bound && stack->index >= lower_bound)
			return (steps);
		steps++;
		stack = stack->next;
	}
	return (steps);
}

int	rotate_count(t_list *stack, int index)
{
	int	steps;

	steps = 0;
	while (stack)
	{
		if (stack->index == index)
			return (steps);
		steps++;
		stack = stack->next;
	}
	return (steps);
}
