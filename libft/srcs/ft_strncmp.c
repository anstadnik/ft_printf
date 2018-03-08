/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 21:47:12 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:06 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Lexicographically compare the null-
** terminated strings s1 and s2.
** Compares not more than n characters.
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		if (!--n)
			return (0);
		else
			i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
