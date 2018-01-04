/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 22:22:59 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:31 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Appends string src to the end of dst.  It will append at most
** dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless
** dstsize is 0 or the original dst string was longer than dstsize (in prac-
** tice this should not happen as it means that either dstsize is incorrect or
** that dst is not a proper string).
*/

#include "libft.h"

size_t	ft_strlcat(char *s1, char *s2, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (ft_strlen(s1) + 1 >= size)
		return (size + ft_strlen(s2));
	i = ft_strlen(s1);
	size -= ft_strlen(s1);
	while (s2[j])
	{
		if (!--size)
			break ;
		else
			s1[i++] = s2[j++];
	}
	s1[i] = '\0';
	return (ft_strlen(s1) + ft_strlen(s2) - j);
}
