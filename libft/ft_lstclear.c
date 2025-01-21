/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:55:00 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/07 21:11:31 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
#include <stdio.h>

void del(void *s)
{
	free(s);
}

int	main()
{
	char *s1 = malloc(2*sizeof(char));
	char *s2 = malloc(2*sizeof(char));
	char *s3 = malloc(2*sizeof(char));
	*s1 = '2';
	*s2 = '3';
	*s3 = '4';
	t_list *lst1 = ft_lstnew(s1);
	t_list *lst2 = ft_lstnew(s2);
	t_list *lst3 = ft_lstnew(s3);
	lst2->next = lst3;
	lst1->next = lst2;
	ft_lstclear(&lst1, del);
	printf("%p\n", lst1);
	return (0);
}
*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*tmp;

	curr = *lst;
	while (curr)
	{
		tmp = curr->next;
		ft_lstdelone(curr, del);
		curr = tmp;
	}
	*lst = NULL;
}
