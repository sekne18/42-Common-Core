/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 21:18:50 by jans              #+#    #+#             */
/*   Updated: 2024/10/14 14:52:22 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*orig;
	t_list	*data;

	if (!lst || !f || !del)
		return (NULL);
	orig = NULL;
	while (lst)
	{
		data = f(lst->content);
		new = ft_lstnew(data);
		if (!new)
		{
			free(data);
			ft_lstclear(&orig, del);
			return (NULL);
		}
		ft_lstadd_back(&orig, new);
		lst = lst->next;
	}
	return (orig);
}
