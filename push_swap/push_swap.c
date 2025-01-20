/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:45:14 by jsekne            #+#    #+#             */
/*   Updated: 2024/11/19 14:51:14 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc < 2)
		return (1);
	if (!validate_args(argc, argv, &stack_a))
	{
		ft_putstr_fd("Error\n", 2);
		ft_lstclear(&stack_a);
		return (0);
	}
	push_swap(&stack_a, &stack_b);
	ft_lstclear(&stack_a);
	return (1);
}

void	push_swap(t_list **stack_a, t_list **stack_b)
{
	int	len;

	len = ft_lstsize(*stack_a);
	compress_numbers(stack_a, len);
	if (is_sorted(*stack_a, 1))
		return ;
	else if (len == 2)
		sa(stack_a, 0);
	else if (len > 2 && len < 6)
		mini_sort(stack_a, stack_b, len);
	else if (len <= 100)
		merge_sort(stack_a, stack_b);
	else
		radix_sort(stack_a, stack_b);
}
