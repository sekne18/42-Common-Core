/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:29:49 by jans              #+#    #+#             */
/*   Updated: 2024/10/20 09:30:43 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_list **stack_a)
{
	rev_rotate(stack_a);
	ft_putstr_fd("rra\n", 1);
}

void	rrb(t_list **stack_b)
{
	rev_rotate(stack_b);
	ft_putstr_fd("rrb\n", 1);
}

void	rrr(t_list **stack_a, t_list **stack_b)
{
	rev_rotate(stack_a);
	rev_rotate(stack_b);
	ft_putstr_fd("rrr\n", 1);
}

void rev_rotate(t_list **stack)
{
	t_list	*head;
	t_list	*tail;
	
	if (!*stack)
		return ;
	head = *stack;
	tail = ft_lstlast(head);
	while (head)
	{
		if (!head->next->next)
		{
			head->next = NULL;
			break ;
		}
		head = head->next;
	}
	tail->next = *stack;
	*stack = tail;
}
