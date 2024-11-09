/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:28:23 by jans              #+#    #+#             */
/*   Updated: 2024/10/21 09:47:31 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_list **stack_a, t_list **stack_b, int bonus)
{
	if (!bonus)
		ft_putstr_fd("pa\n", 1);
	push(stack_a, stack_b);
}

void	pb(t_list **stack_a, t_list **stack_b, int bonus)
{
	if (!bonus)
		ft_putstr_fd("pb\n", 1);
	push(stack_b, stack_a);
}

void	push(t_list **to, t_list **from)
{
	t_list	*head_to;
	t_list	*head_from;
	t_list	*tmp;

	if (!*from)
		return ;
	head_to = *to;
	head_from = *from;
	tmp = head_from;
	head_from = head_from->next;
	*from = head_from;
	if (!head_to)
	{
		head_to = tmp;
		head_to->next = NULL;
		*to = head_to;
	}
	else
	{
		tmp->next = head_to;
		*to = tmp;
	}
}
