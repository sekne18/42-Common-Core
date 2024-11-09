/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:17:11 by jans              #+#    #+#             */
/*   Updated: 2024/11/09 11:25:27 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rot_to_pos(int count, t_list **stack_b, void (*op)(t_list **stack_b,
			int bouns))
{
	while (count--)
		op(stack_b, 0);
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
