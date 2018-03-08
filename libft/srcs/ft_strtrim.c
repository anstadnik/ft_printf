/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 15:30:30 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 19:37:03 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a copy of the string
** given as argument without whitespaces at the beginning or at
** the end of the string. Will be considered as whitespaces the
** following characters ’ ’, ’\n’ and ’\t’. If s has no whitespaces
** at the beginning or at the end, the function returns a
** copy of s. If the allocation fails the function returns NULL.
*/

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	beg;
	size_t	sz;

	i = 0;
	sz = 0;
	beg = 0;
	if (!s)
		return (NULL);
	while (ft_iswhitespace(s[beg]))
		beg++;
	while (s[i + beg])
		if (!ft_isspace(s[beg + i++]))
			sz = i;
	return (ft_strsub(s, (unsigned int)beg, sz));
}
