/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 14:12:48 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:39 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Locates the first occurrence of the null-terminated
** string needle in the null-terminated string haystack.
*/

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	i;

	if (!*s2)
		return ((char *)s1);
	while (*s1)
	{
		if (*s1 == *s2)
		{
			i = 0;
			while (s2[i] == s1[i])
				if (!s2[++i])
					return ((char *)s1);
		}
		s1++;
	}
	return (NULL);
}
