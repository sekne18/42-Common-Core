/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:09:44 by jans              #+#    #+#             */
/*   Updated: 2024/10/13 18:30:41 by jsekne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" 

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*arr;
	int		i;

	i = 0;
	arr = malloc((str_length(s1, s2) + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	while (*s1)
		arr[i++] = *s1++;
	while (*s2)
		arr[i++] = *s2++;
	arr[i] = '\0';
	return (arr);
}

int	str_length(const char *s1, const char *s2)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (s1[i])
		i++;
	while (s2[len])
		len++;
	return (i + len);
}

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*new;
	int		len;

	len = 0;
	while (s[len])
		len++;
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	len = -1;
	while (s[++len])
		new[len] = s[len];
	new[len] = '\0';
	return (new);
}

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
