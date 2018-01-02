/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astadnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:53:45 by astadnik          #+#    #+#             */
/*   Updated: 2017/11/09 13:14:24 by astadnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Copies len bytes from string src to string dst.  The two strings may
** overlap; the copy is always done in a non-destructive manner.
*/

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	if (s1 == s2)
		return (s1);
	if (s1 < s2)
		return (ft_memcpy(s1, s2, n));
	while (n--)
		((char *)s1)[n] = ((char *)s2)[n];
	return (s1);
}
