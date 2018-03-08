/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 16:21:53 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:13:55 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Compares byte string s1 against byte string s2.  Both strings are assumed
** to be n bytes long.
*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		if (!--n)
			return (0);
		else
			i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
