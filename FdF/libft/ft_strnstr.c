/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jan <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 23:28:28 by jan               #+#    #+#             */
/*   Updated: 2024/10/10 18:27:18 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*start;
	const char	*l;
	size_t		l_len;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (*big && len-- > 0)
	{
		start = big;
		l = little;
		l_len = len + 1;
		while (*l && *big && *l == *big && l_len-- > 0)
		{
			l++;
			big++;
		}
		if (*l == '\0')
			return ((char *)start);
		big = start + 1;
	}
	return (NULL);
}
