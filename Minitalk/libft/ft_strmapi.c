/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jans <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 09:04:46 by jans              #+#    #+#             */
/*   Updated: 2024/10/06 23:30:45 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

/*
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int main()
{
	printf("%s\n", ft_strmapi("This is campus 19!", to_upper));
	return (0);
}
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	int		i;

	i = 0;
	while (s[i])
		i++;
	new = malloc((i + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = -1;
	while (s[++i])
		new[i] = f(i, s[i]);
	new[i] = '\0';
	return (new);
}
/*
char	to_upper(unsigned int i, char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
*/
