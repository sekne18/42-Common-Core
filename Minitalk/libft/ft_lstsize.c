/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsekne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:33:18 by jsekne            #+#    #+#             */
/*   Updated: 2024/10/07 16:45:45 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*#include <stdio.h>

int	main()
{
	t_list *lst1 = ft_lstnew("2");
	t_list *lst2 = ft_lstnew("3");
	t_list *lst3 = ft_lstnew("4");
	
	lst2->next = lst3;
	lst1->next = lst2;
	printf("%i\n", ft_lstsize(lst1));
	return (0);
}
*/
int	ft_lstsize(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
