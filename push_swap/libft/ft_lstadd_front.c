/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:05:21 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/07 16:32:22 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

/*
int	main()
{
	t_list *lst1 = ft_lstnew("2");
	t_list *lst2 = ft_lstnew("3");
	t_list *lst3 = ft_lstnew("4");
	
	lst2->next = lst3;
	lst1->next = lst2;

	t_list *new = ft_lstnew("1");
	ft_lstadd_front(&lst1, new);

	while (lst1)
	{
		printf("%s\n", (char *)lst1->content);
		lst1 = lst1->next;
	}
	return (0);
}
*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
