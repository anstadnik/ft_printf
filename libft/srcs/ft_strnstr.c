/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 14:23:07 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:27 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Locates the first occurrence of the null-terminated
** string needle in the string haystack, where not more than len characters
** are searched.  Characters that appear after a `\0' character are not
** searched.
*/

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;

	if (!*s2)
		return ((char *)s1);
	while (len--)
	{
		if (*s1 == *s2)
		{
			i = 0;
			while (s2[i] == s1[i] && i <= len)
				if (!s2[++i])
					return ((char *)s1);
			if (!s1[i])
				return (NULL);
		}
		if (!*s1++)
			return (NULL);
	}
	return (NULL);
}
