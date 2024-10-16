/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:28:12 by jans              #+#    #+#             */
/*   Updated: 2024/10/16 22:21:49 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_list **stack_a)
{
	t_list	*curr;
	t_list	*next;
	t_list	*prev;

	prev = NULL;//Create a null obj
	curr = *stack_a;
	next = NULL;
	if (!curr || !curr->next)
		return ;
	while (curr->next)
	{
		next = curr->next;
		if (!next->next)
		{
			curr->next = next->next;
			next->next = curr;
			prev->next = next;
			break ;
		}
		prev = curr;
		curr = next;
	}
}
