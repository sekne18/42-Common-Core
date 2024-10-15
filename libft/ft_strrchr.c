/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jan <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 11:13:59 by jan               #+#    #+#             */
/*   Updated: 2024/10/11 22:22:43 by jans             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last;

	if ((unsigned char)c > 127)
		return ((char *)s);
	last = (char *)0;
	i = 0;
	while ((unsigned char)s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			last = (char *)&s[i];
		i++;
	}
	if ((unsigned char)c == (unsigned char)s[i])
		last = (char *)&s[i];
	return (last);
}
