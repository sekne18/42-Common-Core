/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:29:49 by jans              #+#    #+#             */
/*   Updated: 2024/10/17 15:54:52 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_list **stack_a)
{
	t_list	*head;
	t_list	*last;
	
	last = *stack_a;
	head = *stack_a;
	if (!head || !head->next)
		return ;
	while (last->next)
		last = last->next;
	*stack_a = head->next;
	head->next = NULL;
	last->next = head;
}

void	rrb(t_list **stack_b)
{
	t_list	*head;
	t_list	*last;
	
	last = *stack_b;
	head = *stack_b;
	if (!head || !head->next)
		return ;
	while (last->next)
		last = last->next;
	*stack_b = head->next;
	head->next = NULL;
	last->next = head;
}

void	rrr(t_list **stack_a, t_list **stack_b)
{
	rra(stack_a);
	rrb(stack_b);
}
