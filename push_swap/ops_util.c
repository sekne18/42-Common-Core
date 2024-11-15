/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:17:11 by jans              #+#    #+#             */
/*   Updated: 2024/11/15 15:50:29 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rot_to_pos_b(t_list **stack_a, t_list **stack_b)
{
	int can_move;
	int size;
	int	max;
	int	steps_to_rot;
	int count;

	can_move = 1;
	size = ft_lstsize(*stack_b);
	max = ft_lstmax_idx(*stack_b);
	steps_to_rot = rotate_count(*stack_b, max);
	if (steps_to_rot > size / 2)
	{
		count = size - steps_to_rot;
		while (count--)
		{
			if (next_to_be_moved(*stack_b) && can_move)
			{
				pa(stack_a, stack_b, 0);
				can_move--;
			}
			rrb(stack_b, 0);
		}
	}
	else
	{
		count = steps_to_rot;
		while (count--)
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

void	rot_to_pos_a(int count, t_list **stack, void (*op)(t_list **stack_b,
			int bonus))
{
	while (count--)
	{
		op(stack, 0);
	}
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

int	rotate_count_median(t_list *stack, int median)
{
	int	steps;

	steps = 0;
	while (stack)
	{
		if (stack->index < median)
			return (steps);
		steps++;
		stack = stack->next;
	}
	return (steps);
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

void	possible_swap(t_list **stack_b)
{
	int	size;
	
	size = ft_lstsize(*stack_b);
	if (size < 3)
		return ;
	if ((*stack_b)->index < (*stack_b)->next->index)
		sb(stack_b, 0);
}

int	next_to_be_moved(t_list *stack)
{
	int	moving;

	moving = ft_lstmax_idx(stack);
	if ((moving - stack->index) == 1)
		return (1);
	return (0);
}
