/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:28:45 by jans              #+#    #+#             */
/*   Updated: 2024/10/21 09:48:41 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_list **stack_a, int bonus)
{
	rotate(stack_a);
	if (!bonus)
		ft_putstr_fd("ra\n", 1);
}

void	rb(t_list **stack_b, int bonus)
{
	rotate(stack_b);
	if (!bonus)
		ft_putstr_fd("rb\n", 1);
}

void	rr(t_list **stack_a, t_list **stack_b, int bonus)
{
	rotate(stack_a);
	rotate(stack_b);
	if (!bonus)
		ft_putstr_fd("rr\n", 1);
}

void	rotate(t_list **stack)
{
	t_list	*tail;
	t_list	*head;

	if (!*stack)
		return ;
	head = *stack;
	tail = ft_lstlast(head);
	*stack = head->next;
	head->next = NULL;
	tail->next = head;
}
