/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jan <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:06:22 by jan               #+#    #+#             */
/*   Updated: 2024/10/11 15:30:12 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		contains(char const *set, char c);

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*new;
	size_t		l;
	size_t		r;
	int			i;

	l = 0;
	r = ft_strlen(s1);
	if (!s1)
		return ((char *)s1);
	while (contains(set, s1[l]))
		l++;
	if (l == r)
		return (ft_strdup(""));
	while (r > l && contains(set, s1[r - 1]))
		r--;
	new = malloc((r - l + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (l < r)
		new[i++] = s1[l++];
	new[i] = '\0';
	return (new);
}

int	contains(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}
