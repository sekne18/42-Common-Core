/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:50:00 by jans              #+#    #+#             */
/*   Updated: 2024/10/16 20:51:47 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%d", lst->number);
		if (lst->next)
			printf(" -> ");
		lst = lst->next;
	}
	printf("\n");
}
