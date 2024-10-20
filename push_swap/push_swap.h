/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:45:23 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/20 15:53:54 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "./libft/libft.h"

int		validate_args(int argc, char **argv, t_list **stack);
int		valid_arg_format(char *str);
int		has_duplicates(t_list **stack, t_list *node);
int		ft_arrlen(char **arr);
int		fill_list(int len, int type, t_list **stack, char **argv);
int		find_max_bits(t_list *stack_a);
int		ft_lstmax_idx(t_list *stack);
int		ft_lstlast_idx(t_list *stack);
int		is_sorted(t_list *stack);
int		ft_lstmin(t_list *stack);
int		ft_lst_nextmin(t_list *stack);
void	radix_sort_b(t_list **stack_a, t_list **stack_b, int max_bit, int i);
void	sort_3(t_list **stack_a);
void	sort_5(t_list **stack_a, t_list **stack_b, int len);
void	mini_sort(t_list **stack_a, t_list **stack_b, int len);
void	push(t_list **to, t_list **from);
void	rotate(t_list **stack);
void	swap(t_list **stack);
void	rev_rotate(t_list **stack);
void	push_swap(t_list **stack_a, t_list **stack_b);
void	compress_numbers(t_list **stack_a, int size);
void	print_list(t_list *lst);
void	radix_sort(t_list **stack_a, t_list **stack_b);
void	sa(t_list **stack_a);
void	sb(t_list **stack_b);
void	ss(t_list **stack_a, t_list **stack_b);
void	pa(t_list **stack_a, t_list **stack_b);
void	pb(t_list **stack_a, t_list **stack_b);
void	ra(t_list **stack_a);
void	rb(t_list **stack_b);
void	rr(t_list **stack_a, t_list **stack_b);
void	rra(t_list **stack_a);
void	rrb(t_list **stack_b);
void	rrr(t_list **stack_a, t_list **stack_b);
#endif
