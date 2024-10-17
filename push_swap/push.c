/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:28:23 by jans              #+#    #+#             */
/*   Updated: 2024/10/17 21:35:26 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_list **stack_a, t_list **stack_b)
{
	t_list	*curr_b;

	ft_putstr_fd("pa\n", 1);
	curr_b = *stack_b;
	if (!*stack_b)
		return ;	
	if (!curr_b->next)
	{
		ft_lstadd_back(stack_a, curr_b);
		*stack_b = NULL;
		return ;
	}
	while (curr_b->next->next)
		curr_b = curr_b->next;
	ft_lstadd_back(stack_a, curr_b->next);
	curr_b->next = NULL;
}

void	pb(t_list **stack_a, t_list **stack_b)
{
	t_list	*curr_a;

	ft_putstr_fd("pb\n", 1);
	curr_a = *stack_a;
	if (!*stack_a)
		return ;	
	if (!curr_a->next)
	{
		ft_lstadd_back(stack_b, curr_a);
		*stack_a = NULL;
		return ;
	}
	while (curr_a->next->next)
		curr_a = curr_a->next;
	ft_lstadd_back(stack_b, curr_a->next);
	curr_a->next = NULL;
}
