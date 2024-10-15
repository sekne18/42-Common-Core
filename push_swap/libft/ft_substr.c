/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jan <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 07:26:29 by jan               #+#    #+#             */
/*   Updated: 2024/10/11 12:42:39 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int			s_i;
	char		*str;
	size_t		i;

	i = ft_strlen(s);
	if (i <= start)
		i = 0;
	else
	{
		if (len < ft_strlen(s + start))
			i = len;
		else
			i = ft_strlen(s + start);
	}
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	s_i = 0;
	while (i && s[start] && len--)
		str[s_i++] = s[start++];
	str[s_i] = '\0';
	return (str);
}
